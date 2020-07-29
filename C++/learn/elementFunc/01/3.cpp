/*************************************************************************
	> File Name: 2.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月05日 星期五 10时41分03秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Foo{
public:
    //Foo(int v,int v2,string &s) : value(v),value2(v2),str(s) {}
    
    Foo(int i,int i2,string s) : value(i),value2(i2),str(s) {

    }
    Foo(int i,int i2) : value(i),value2(i2) {

    }
    void f() {
        cout << "f(" << this->value << ", "<< this->str << " , "<< this->value2 << ")" << endl;
    }
    void g() {
        cout << "g(" << this->value << ", "<< this->str << " , "<< this->value2 << ")" << endl;
    }
private:
    int value = 1;
    int value2 = 2;
    string str = "good";
};

void apply(Foo* foo1, Foo* foo2, void(Foo::*fun)()) {
    (foo1->*fun)();
    (foo2->*fun)();
}

int main() {
    std::string str = "gsaa";
    Foo foo1{1,2,std::move(str)};
    Foo foo2{2,3};
    apply(&foo1,&foo2,&Foo::f);
    apply(&foo1,&foo2,&Foo::g);
}
