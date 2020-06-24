/*************************************************************************
    > File Name: include/peripherals/IDcardidentify.h
    > Author: chen bingyi
    > Mail:
    > Created Time: 2019年10月15日 星期二 15时09分45秒
 ************************************************************************/

#ifndef _IDCARDIDENTIFY_H
#define _IDCARDIDENTIFY_H
#include <atomic>
#include <iostream>
#include <thread>
#include "utils/rs_log.h"
extern "C" {
#include "libtermb.h"
}
class IDcardbase
{
public:
    static IDcardbase* getInstance() {
        if(instance_ == nullptr) {
            instance_ = new IDcardbase();
        }
        return instance_;
    }
    typedef std::function<void(const std::string&,const std::string&)> DoneCB;
    typedef struct
    {
        std::string name;
        std::string sex;
        std::string nation;
        std::string birthday;
        std::string address;
        std::string cardid;
        std::string issuing_authority;
        std::string useful_life;
    }PersonInfo;

    bool init();
    void start_identify(DoneCB cb=DoneCB());
    void stop_identify();

private:

    int GHC_InitUSB();
    int GHC_ReadSAMIDStr(char* SAMIDStr);
    int GHC_ReadBaseMsg(char* szTxt, char* szBmp);
    int GHC_ReadBaseMsg_loop(char* szTxt, char* szBmp);
    int GHC_ReadFPMsg(char* szTxt, char* szBmp, char* szFinger, int *iFingerLen);
    int GHC_ReadFPMsg_loop(char* szTxt, char* szBmp, char* szFinger, int *iFingerLen);
    void GHC_CloseUSB();

    void run();
    void get_detailed_info(char *szTxt,PersonInfo &info);

private:
    IDcardbase();
    ~IDcardbase();
    static IDcardbase *instance_;
    std::atomic<bool> isRunning_;
    std::thread identify_thead_;
    DoneCB done_cb_;

    class GC // 垃圾回收类
    {
        public:
            GC()
            {
                //cout<<"GC construction"<<endl;
            }
            ~GC()
            {
                //cout<<"GC destruction"<<endl;
                // We can destory all the resouce here, eg:db connector, file handle and so on
                if (instance_ != NULL)
                {
                    std::cerr << "destroying IDcardReader GC" << std::endl;
                    delete instance_;
                    instance_ = NULL;
                    logi("destroy IDcardReader GC");
                }
            }
    };
    static GC gc;  //垃圾回收类的静态成员
};

#endif
