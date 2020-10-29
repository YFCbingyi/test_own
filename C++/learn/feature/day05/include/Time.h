/***************************************************
@File Name: Time.h
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-28 10:46:02
****************************************************/

#ifndef _MY_TIME_H
#define _MY_TIME_H

#include <iostream>

class TT{
public:
    TT & operator=(const TT&) {
        std::cout << "复制TT" << std::endl;
        return *this;
    }
};

class MyTime
{
private:
    /* data */
    TT t;
    int i;
public:
    MyTime(/* args */);
    ~MyTime();

    MyTime& operator=(const MyTime& time);
};

#endif