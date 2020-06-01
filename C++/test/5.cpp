/*************************************************************************
	> File Name: 5.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月01日 星期一 15时30分13秒
 ************************************************************************/

/*
*静态成员变量继承的话，会将那块内存共享出去，不管父类或子类修改，都会改变
* */

#include<iostream>
using namespace std;

class A{
public:
    A() {}
    ~A() {}
    static int a;
    static void set();
};

int A::a = 10;
void A::set() {
    a = 17;
}

class B : public A{
public:
    B() {}
    ~B() {}
    static void set(); 
};

void B::set() {
    a = 27;
}

int main() {
    A a;
    std::cout << a.a << std::endl;
    B b;
    std::cout << b.a << std::endl;
    b.a = 11;
    std::cout << a.a << std::endl;
    a.set();
    std::cout << a.a << std::endl;
    std::cout << b.a << std::endl;
    a.a = 222;
    std::cout << a.a << std::endl;
    std::cout << b.a << std::endl;
    b.set();
    std::cout << a.a << std::endl;
    std::cout << b.a << std::endl;
}
