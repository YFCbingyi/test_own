/*************************************************************************
    > File Name: src/IDcardidentify.cpp
    > Author: chen bingyi
    > Mail:
    > Created Time: 2019年10月15日 星期二 15时09分22秒
 ************************************************************************/

#include "peripherals/IDcardbase.h"
#include "utils/rs_log.h"
#include "peripherals/func.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <memory.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <iconv.h>
#include <functional>

#define PRINT_LOG	1

#include<iostream>
IDcardbase* IDcardbase::instance_ = NULL;
IDcardbase::IDcardbase() {

}
IDcardbase::~IDcardbase() {
    if(identify_thead_.joinable()) {
        identify_thead_.join();
    }
}

bool IDcardbase::init() {
    if(GHC_InitUSB() != 0) {
        loge("IDcardbase::run open usb error");
        return false;
    }
    return true;
}

void IDcardbase::start_identify(DoneCB cb) {
    if(cb != nullptr)
        done_cb_ = cb;
    else
        loge("DoneCB is nullptr");
    if(identify_thead_.joinable()) {
        identify_thead_.join();
        return;
    }
    isRunning_ = true;
    identify_thead_ = std::thread(&IDcardbase::run, this);
}
void IDcardbase::stop_identify() {
    isRunning_ = false;
}

void IDcardbase::run() {
    
    char SAMIDStr[64];

    char szTxt_GB2312[500] = {0x00};
    char szTxt_UTF[1024] = {0x00};
    char szBmp[38862] = {0x00};
    PersonInfo info;
    while(isRunning_) {
        memset(SAMIDStr, 0x00, sizeof(SAMIDStr));
        if(GHC_ReadSAMIDStr(SAMIDStr) == 0) {
            if(PRINT_LOG) {
                printf("SAMID = [%s] .\n", SAMIDStr);
            } else {
                if(PRINT_LOG)printf("Get SAMID error .\n");
            }
        }
        /** 读取模块SAMID 结束**/


        /** 读取身份证基本信息 开始**/
        if(GHC_ReadBaseMsg(szTxt_GB2312, szBmp) == 0) {
            //保存bmp

            if(PRINT_LOG)
                printf("szTxt_GB2312 is: %s\n", szTxt_GB2312);
            //转码
            g2u(szTxt_GB2312, strlen(szTxt_GB2312), szTxt_UTF, sizeof(szTxt_UTF));
            if(PRINT_LOG)
                printf("szTxt_UTF is: %s \n", szTxt_UTF);
            get_detailed_info(szTxt_UTF,info);
//            std::string path = "/"+info.cardid+".bmp";
//            SaveBMP(szBmp, sizeof(szBmp),path);
            if(done_cb_ != nullptr)
                done_cb_(info.cardid,info.name);
            isRunning_ = false;
        } else {
            if(PRINT_LOG)printf("Read IDCard Fail ! .\n");
        }
        /** 读取身份证基本信息 结束**/
        sleep(1);
    }
    CloseComm();
}

void IDcardbase::get_detailed_info(char *szTxt,PersonInfo &info) {
    try{
    std::string str = szTxt;
    std::size_t found  = str.find_first_of("|");
    info.name = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    info.sex = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    info.nation = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    info.birthday = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    info.address = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    info.cardid = str.substr(0,found);
    str = str.substr(found+1,str.length());
    found  = str.find_first_of("|");
    info.issuing_authority = str.substr(0,found);
    str = str.substr(found+1,str.length());
    info.useful_life = str;
    } catch(std::exception &e) {
        loge("IDcardBase get info error %s",e.what());    
    }
}

// open 成功返回 0 ，失败返回 -1 ；
int IDcardbase::GHC_InitUSB() {
    int iResult = 0;
    char UsbDevice[] = "/dev/IDreader";

    iResult = InitComm(UsbDevice);
    if (iResult != 1) {
        if(PRINT_LOG)printf("InitComm error:%d\n", iResult);
        CloseComm();
        iResult =  -1;
    } else
        iResult = 0;

    return iResult;
}

//读取模块SAMID
int IDcardbase::GHC_ReadSAMIDStr(char* SAMIDStr) {
    int iResult = 0;
    char SAMID[50];

    memset(SAMID, 0x00, sizeof(SAMID));
    iResult = GetSamdId(SAMID);
    if(iResult == 1) {
        memcpy(SAMIDStr, SAMID, strlen(SAMID));
        iResult = 0;
    } else {
        iResult = -1;
    }
    return iResult;
}


//读取身份证基本信息
int IDcardbase::GHC_ReadBaseMsg(char* szTxt, char* szBmp) {
    char szWlt[2048] = {0};

    if(FindCardCmd() != 0x9f) {
        if(PRINT_LOG)printf("find card fail ! \n");
        return -101;	//find card fail
    }

    if(SelCardCmd() != 0x90) {
        if(PRINT_LOG)printf("find card fail ! \n");
        return -102;	//select card fail
    }

    if(ReadCard(szTxt, szWlt, szBmp) != 1) {
        if(PRINT_LOG)printf("ReadCard error\n");
        return -103;
    }

    return 0;
}


//读取身份证基本信息【支持循环调用】
int IDcardbase::GHC_ReadBaseMsg_loop(char* szTxt, char* szBmp) {
    char szWlt[2048] = {0};

    if(ReadCard(szTxt, szWlt, szBmp) != 1) {
        if(FindCardCmd() != 0x9f) {
            if(PRINT_LOG)printf("find card fail ! \n");
            return -101;	//find card fail
        }

        if(SelCardCmd() != 0x90) {
            if(PRINT_LOG)printf("find card fail ! \n");
            return -102;	//select card fail
        }

        if(ReadCard(szTxt, szWlt, szBmp) != 1) {
            if(PRINT_LOG)printf("ReadCard error\n");
            return -103;
        }
    }
    return 0;
}

//读取身份证信息，带指纹
int IDcardbase::GHC_ReadFPMsg(char* szTxt, char* szBmp, char* szFinger, int *iFingerLen) {
    char szWlt[2048] = {0};

    if(FindCardCmd() != 0x9f) {
        if(PRINT_LOG)printf("find card fail ! \n");
        return -101;	//find card fail
    }

    if(SelCardCmd() != 0x90) {
        if(PRINT_LOG)printf("find card fail ! \n");
        return -102;	//select card fail
    }

    if(ReadCardExt(szTxt, szWlt, szBmp) != 1) {
        if(PRINT_LOG)printf("ReadCard error\n");
        return -103;
    }

    *iFingerLen = GetFingerData(szFinger);
    return 0;
}

//读取身份证信息，带指纹【支持循环调用】
int IDcardbase::GHC_ReadFPMsg_loop(char* szTxt, char* szBmp, char* szFinger, int *iFingerLen) {
    char szWlt[2048] = {0x00};

    if(ReadCardExt(szTxt, szWlt, szBmp) != 1) {
        if(FindCardCmd() != 0x9f) {
            if(PRINT_LOG)printf("find card fail ! \n");
            return -101;	//find card fail
        }

        if(SelCardCmd() != 0x90) {
            if(PRINT_LOG)printf("find card fail ! \n");
            return -102;	//select card fail
        }

        if(ReadCardExt(szTxt, szWlt, szBmp) != 1) {
            if(PRINT_LOG)printf("ReadCard error\n");
            return -103;
        }
    }

    *iFingerLen = GetFingerData(szFinger);
    return 0;
}


//关闭
void IDcardbase::GHC_CloseUSB() {
    CloseComm();
}



