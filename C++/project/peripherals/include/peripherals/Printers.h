/*************************************************************************
    > File Name: include/peripherals/Printers.h
    > Author: chen bingyi
    > Mail:
    > Created Time: 2019年10月14日 星期一 11时48分23秒
 ************************************************************************/


#ifndef PRINTERS_H
#define PRINTERS_H

#include "SerialDev.h"
#include <string>
#include <iostream>
#include "func.h"
#include <atomic>
#include "utils/rs_log.h"

class Printers
{
    public:
        enum DUIQIWAY{D_LEFT,D_MIDDLE,D_RIGHT};
    public:
        static Printers* getInstance() {
            if(instance_ == nullptr) {
                instance_ = new Printers();
            }
            return instance_;
        }
       
        bool print_Taian_service_center(std::string &ticketNO,std::string &windowNo,std::string &serviceArea,std::string &serviceNO,std::string &date,std::string &applicationPersoin,std::string &serviceName,int waitPerson,std::string &qrData);
        
        bool hasPaper() {
            return P_check_paper();
        }
        
        bool init();
        bool print_img(unsigned char _data[]);
        bool sendData(unsigned char data_[],int length);
        bool P_print_line(); //打印换行

    private:
        Printers();
        ~Printers();
        bool P_initial();   //初始化打印机
        bool P_print_str(std::string &str); //把要打印的字符串放入缓冲区
        bool P_print_chinese(char str[]); //把要打印的字符串放入缓冲区
        bool P_set_chinese(bool flag);
        bool P_print_enter();   //打印回车
        bool P_auto_test(); //自测试
        bool P_set_table();   //打印回车
        bool P_jump_table();   //打印回车
        bool P_status_timer();
        bool P_set_formatway(DUIQIWAY way); //设置对齐方式
        bool P_set_wordsize(int size);
        bool P_set_wordbold();
        bool P_cancel_wordbold();
        bool show_str(std::string &cmd);
        bool show(unsigned char cmd[]);
        bool P_set_QRsize(unsigned char size);
        bool P_set_QRdata(unsigned int length,unsigned char *pdata);
        bool P_check_QRdata();
        bool P_print_QRdata();
        bool P_print(std::string &data,DUIQIWAY format,int worldsize,bool is_chinese,bool is_blod,bool need_initial = true);
        bool P_printQR(std::string &data,DUIQIWAY format,int qrsize);
        bool P_check_paper();
        bool P_printImg(std::string &baseImg);
    private:
        static Printers *instance_;

        SerialDev serial_dev_;
        std::atomic<bool> serial_ready_;


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
                        std::cerr << "destroying Printer GC" << std::endl;
                        delete instance_;
                        instance_ = NULL;
                        logi("destroy Printer GC");
                    }
                }
        };
        static GC gc;  //垃圾回收类的静态成员
};

#endif // PRINTKER_H
