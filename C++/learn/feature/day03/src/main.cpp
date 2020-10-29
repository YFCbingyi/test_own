/***************************************************
@File Name : main.cpp
@Project : 
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-17 17:15:15
****************************************************/

#include <iostream>

#include "MyTime.h"

using namespace std;

// void func() const  //const 不能修饰普通函数，只能修饰成员函数，表示对象内成员变量和状态不能被改变
// {
//     return;
// }

int main(int argc,char **argv)
{

    //类中 const
    MyTime t1;
    cout << "&t1 ="<<&t1 << endl;
    t1.add();
    const MyTime t2;
    cout << "&t2 ="<<&t2 << endl;
    // t2.add();
    t2.dele();
    t1.dele();
    //类中 mutable 
    //修饰一个成员变量，一旦被mutable修饰，就表示这个变量永远处于可以被修改状态
    //即使在const结尾的函数内，也可以被修改
    MyTime t3;
    cout << "&t3 ="<<&t3 << endl; 
    t3.dele();
    t3.add_hour(1).add_hour(2).add_min(12);
    t3.dele();

    return 0;
}
