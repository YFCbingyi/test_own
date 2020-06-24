/*************************************************************************
	> File Name: 1.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月05日 星期五 10时41分03秒
 ************************************************************************/

#include<iostream>
using namespace std;

struct Foo{
    int value;
    void f() {
        cout << "f(" << this->value << ")" << endl;
    }
    void g() {
        cout << "g(" << this->value << ")" << endl;
    }
};

void apply(Foo* foo1, Foo* foo2, void(Foo::*fun)()) {
    (foo1->*fun)();
    (foo2->*fun)();
}

int main() {
    Foo foo1{1};
    Foo foo2{2};
    apply(&foo1,&foo2,&Foo::f);
    apply(&foo1,&foo2,&Foo::g);
}
