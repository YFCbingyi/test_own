/***************************************************
@File Name: CTempValue.h
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-10-09 16:10:07
****************************************************/

#ifndef _CTEMPVALUE_H
#define _CTEMPVALUE_H

class CTempValue
{
private:
    /* data */
public:
    CTempValue(int val1 = 0,int val2 = 0);
    ~CTempValue();
    void print();

private:
    int val1_;
    int val2_;

};



#endif