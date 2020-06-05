/*************************************************************************
	> File Name: stdfuncpoint1.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月03日 星期三 17时31分37秒
 ************************************************************************/

#include<iostream>
#include<typeinfo>
using namespace std;
using FTtype = int(int,int); //函数类型
typedef int (*pf)(int,int); //函数指针

int func(int a,int b) {
    return a+b;
}

void print(int a,int b,FTtype fn) {
    //编译器将其隐式转换成函数指针
    std::cout << fn(a,b) << std::endl;
    cout << typeid(fn).name() << endl; //PFiiiE
}

int main() {
    print(1,2,func);
    cout << typeid(FTtype).name() << endl; //FiiiE
    cout << typeid(func).name() << endl; //FiiiE
    cout << typeid(decltype(func)).name() << endl; //FiiiE
    cout << typeid(pf).name() << endl; //PFiiiE
    return 0;
}
