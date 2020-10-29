/***************************************************
@File Name: Test.h
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-20 17:20:24
****************************************************/

#ifndef _TEST_H
#define _TEST_H

class Test
{
private:
    /* data */
    const int ciintvalue = 18;
    const char* ccharvalue = "Test";
public:
    Test(/* args */);
    ~Test();

    void Print();
};


#endif