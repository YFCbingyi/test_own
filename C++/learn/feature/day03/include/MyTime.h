/***************************************************
@File Name: Time.h
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-17 17:16:13
****************************************************/

#ifndef _MYTIME_H
#define _MYTIME_H

class MyTime
{
private:
    int hour,min;
    mutable int sec;
    
public:
    MyTime(/* args */);
    ~MyTime();

    void add();
    void dele() const;

    MyTime& add_hour(int hour);
    MyTime& add_min(int min);

};


#endif