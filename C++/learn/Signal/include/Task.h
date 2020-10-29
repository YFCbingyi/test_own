/***************************************************
@File Name: Task.h
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-19 11:30:29
****************************************************/

#ifndef _TASK_H
#define _TASK_H
#include "Signal.h"

class Task
{
public:
    Signal<bool,bool> on_click;
private:
    /* data */
public:
    Task(/* args */);
    ~Task();

    bool start();
    void on_emit_click(bool flag,bool flag2);
};


#endif