/*************************************************************************
    > File Name: include/peripherals/Printers.h
    > Author: chen bingyi
    > Mail:
    > Created Time: 2019年10月14日 星期一 11时48分23秒
 ************************************************************************/

#include "peripherals/Printers.h"
#include "peripherals/func.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

Printers* Printers::instance_ = NULL;

Printers::Printers() : serial_ready_(false){
}

bool Printers::init() {
    serial_dev_.close();

    if(RET_OK != serial_dev_.open("/dev/printer")) {
        printf("serial dev open fail: /dev/printer.\n");
        return -1;
    } else
        printf("serial dev open success.\n");

    if(RET_OK != serial_dev_.init(9600, 8, 'n', 1)) { //todo:
        printf("serial dev init fail.\n");
        return false;
    } else
        printf("serial dev init success.\n");

    serial_ready_ = true;
    return true;
}

bool Printers::sendData(unsigned char data_[],int length) {
    if(serial_ready_) {
        return serial_dev_.write(data_, length) > 0 ? true : false;
    } else {
        printf("serial dev is not initialized.\n");
        return false;
    }
}

bool Printers::P_initial() {
    unsigned char str[2] = {0x1b,0x40};
    return sendData(str,sizeof(str));
}

bool Printers::P_print_str(std::string &str) {
    return serial_dev_.write(str.c_str(), str.length()) > 0 ? true : false;
}

bool Printers::P_print_chinese(char str[]) {
    return serial_dev_.write(str, strlen(str)) > 0 ? true : false;
}

bool Printers::P_set_chinese(bool flag) {
    int num = 0;
    if(flag) {
        unsigned char str[] = {0x1c,0x26,0x00};
        return sendData(str,sizeof(str));
    } else {
        unsigned char str[] = {0x1c,0x2e};
        return sendData(str,sizeof(str));
    }

}

bool Printers::P_print_line() {
    unsigned char str[] = {0x0A};
    return sendData(str,sizeof(str));
}

bool Printers::P_print_enter() {
    unsigned char str[] = {0x0D};
    return sendData(str,sizeof(str));
}

bool Printers::P_set_table() {
    unsigned char str[] = {0x1B, 0x44,0x04,0x0A, 0x00};
    return sendData(str,sizeof(str));
}

bool Printers::P_jump_table() {
    unsigned char str[] = {0x09};
    return sendData(str,sizeof(str));
}

bool Printers::P_status_timer() {
    unsigned char str[3] = {0x1d,0x61,0x24};
    return sendData(str,sizeof(str));
}

bool Printers::P_auto_test() {
    unsigned char str[4] = {0x1B,0x40,0x12,0x54};
    return sendData(str,sizeof(str));
}

bool Printers::P_set_formatway(DUIQIWAY way) {
    unsigned char str[3] = {0x1B,0x61};
    if(way == D_LEFT) {
        str[2] = 0x48;
    } else if(way == D_MIDDLE) {
        str[2] = 0x49;
    } else if(way == D_RIGHT) {
        str[2] = 0x50;
    }
    return sendData(str,sizeof(str));
}

bool Printers::P_set_wordsize(int size) {
    unsigned char str[3] = {0x1D,0x21};
    if(size == 1) {
        str[2] = 0x00;
    } else if(size == 2) {
        str[2] = 0x11;
    } else if(size == 3) {
        str[2] = 0x22;
    }
    return sendData(str,sizeof(str));
}

bool Printers::P_set_wordbold() {
    unsigned char str[3] = {0x1B,0x45,0x01};
    return sendData(str,sizeof(str));
}
bool Printers::P_cancel_wordbold() {
    unsigned char str[3] = {0x1B,0x45,0x00};
    return sendData(str,sizeof(str));
}

bool Printers::P_set_QRsize(unsigned char size) {
    unsigned char str[] = {0x1d,0x28,0x6b,0x03,0x00,0x31,0x43,size};
    return sendData(str,sizeof(str));
}

bool Printers::P_set_QRdata(unsigned int length,unsigned char *pdata) {

    unsigned char str[8+static_cast<int>(length)] = {0x1d,0x28,0x6b,static_cast<unsigned char>(length+3),0x00,0x31,0x50,0x30};
    for(int i = 0;i < static_cast<int>(length);i++) {
        str[8+i] = pdata[i];
    }
    return sendData(str,sizeof(str));
}

bool Printers::P_check_QRdata() {
    unsigned char str[] = {0x1D,0x28,0x6B,0x03,0x00,0x31,0x52,0x30};
    return sendData(str,sizeof(str));
}

bool Printers::P_print_QRdata() {
    unsigned char str[] = {0x1D,0x28,0x6B,0x03,0x00,0x31,0x51,0x30};
    return sendData(str,sizeof(str));
}

bool Printers::print_img(unsigned char _data[]) {
    
    return sendData(_data,sizeof(_data));
}

bool Printers::P_check_paper() {
    unsigned char str[] = {0x10,0x04,0x01};
    if(sendData(str,sizeof(str)) <= 0)
        printf("Printers::check paper write failed");
    unsigned char res[3] = {0};
    if(serial_dev_.read((void*)res,1) < 0)
        printf("Printers::check paper read failed");
    printf("res %x",res[0]);
    if(res[0] == 0x12) {
        return true;
    } else if(res[0] == 0x1a){
        return false;
    } else if(res[0] == 0x0c) {
        return false;
    }
    return false;
}

bool Printers::P_print(std::string &data,DUIQIWAY format,int worldsize,bool is_chinese,bool is_blod,bool need_initial) {
    if(!P_check_paper())
        return false;
    if(need_initial) {
        if(!P_initial()) {
            std::cout << "initial failed" <<std::endl;
        }
    }
    P_set_formatway(format);
    P_set_wordsize(worldsize);
    if(is_blod)
        P_set_wordbold();
    if(is_chinese) {
        P_set_chinese(true);
        char str[64] = {0};
        memset(str,0,64);
        StringToChar(data,str,64);
        if(!this->P_print_chinese(str)) {
            std::cout << "write failed" <<std::endl;
        }
    } else {
        P_print_str(data);
    }
    return true;
}

bool Printers::P_printQR(std::string &qrData,DUIQIWAY format,int qrsize) {
    if(!this->P_set_formatway(format)) {
        std::cout << "set format way failed" <<std::endl;
    }
    this->P_set_QRsize(qrsize);
    char qr[64] = {0};
    qrData.copy(qr,qrData.size(),0);
    unsigned int length = strlen(qr);
    unsigned char *qdata = (unsigned char*)qr;
    this->P_set_QRdata(length,qdata);
    this->P_check_QRdata();
    this->P_print_QRdata();
}

bool Printers::print_Taian_service_center(std::string &ticketNO,std::string &windowNo,std::string &serviceArea,std::string &serviceNO,std::string &date,std::string &applicationPersoin,std::string &serviceName,int waitPerson,std::string &qrData) {
    //1
    std::string title1 = "泰安市";
    if(!P_print(title1,D_MIDDLE,2,true,true))
        return false;
    P_print_line();
    //2
    std::string title2 = "政务服务中心";
    if(!P_print(title2,D_MIDDLE,2,true,true))
        return false;
    P_print_line();
    //3
    std::string ticket = "票号 ："+ticketNO;
    if(!P_print(ticket,D_MIDDLE,2,true,true))
        return false;
    P_print_line();
    //4
    std::string window = "办理窗口 : ";
    if(!P_print(window,D_LEFT,1,true,false))
        return false;
    if(!P_print(windowNo,D_LEFT,1,false,true,false))
        return false;
    P_print_line();
    //5
    std::string service_left = "服务区域 ："+serviceArea;
    if(!P_print(service_left,D_LEFT,1,true,false))
        return false;
    std::string service_right = "（"+serviceNO+"）";
    if(!P_print(service_right,D_LEFT,1,true,true,false))
        return false;
    P_print_line();
    //6
    std::string date_complete = "办理日期 ："+date;
    if(!P_print(date_complete,D_LEFT,1,true,false))
        return false;
    P_print_line();
    //7
    std::string sy = "*";
    if(!P_print(sy,D_LEFT,1,false,false))
        return false;
    std::string tishi = "请您留意上述窗口屏幕显示票号，至您票号的窗口办理";
    if(!P_print(tishi,D_LEFT,1,true,false,false))
        return false;
    P_print_line();
    //8
    if(!applicationPersoin.empty()) {
        std::string person = "申请人 ："+applicationPersoin;
        if(!P_print(person,D_LEFT,1,true,false))
            return false;
        P_print_line();
    }
    //9
    std::string service = "业务名称 ："+serviceName;
    if(!P_print(service,D_LEFT,1,true,false))
        return false;
    P_print_line();
    //10
    std::string waitP = "等待人数 ："+std::to_string(waitPerson);
    if(!P_print(waitP,D_LEFT,1,true,false))
        return false;
    P_print_line();
    // 11 QR码

    if(!P_printQR(qrData,D_MIDDLE,8))
        return false;
    P_print_line();
    P_print_enter();
    P_print_enter();
    if(!P_check_paper())
        return false;
    else
        return true;
}
