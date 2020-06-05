/*************************************************************************
	> File Name: stdbindfunc1.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月03日 星期三 17时47分02秒
 ************************************************************************/

#include<iostream>
#include<functional>
using namespace std;

int add(int a,int b) {return a+b;}

auto mod = [](int a,int b){return a%b;};

struct divide{
    int operator()(int denominator,int divisor) {
        return denominator/divisor;
    }
};

int main() {

    int x = 10,y = 3;
    int num = 1;
    cout << "---------------"<< num++ << "-------------" << endl;
    cout << add(x,y) << endl;
    cout << mod(x,y) << endl;
    divide d;
    cout << d(x,y) << endl;
    cout << divide()(y,x) << endl;

    cout << "---------------"<< num++ << "-------------" << endl;
    std::function<int(int,int)> a = add;
    std::function<int(int,int)> b = mod;
    std::function<int(int,int)> c = divide();

    cout << a(1,11) << endl;
    cout << b(4,2) <<endl;
    cout << c(14,3) << endl;
}
