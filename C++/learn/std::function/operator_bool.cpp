/*************************************************************************
	> File Name: operator_bool.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月11日 星期四 16时04分45秒
 ************************************************************************/

#include<iostream>
#include<functional>
using namespace std;

/* std::function<R(Args...)>::operator bool 
 * 检查 *this 是否存储可调用函数对象，即非空
 * 若 *this 存储可调用函数对象则为 true ，否则为 false
* */

void sampleFunction() {
    cout << "This is the simple function\n";
}

void checkFunc(std::function<void()> &func) {
    if(func) {
        std::cout << "Function is not empty\n";
        func();
    } else {
        cout << "function is empty\n";
    }
}

int main() {
    std::function<void()> f1;
    std::function<void()> f2(sampleFunction);

    cout << "f1 :";
    checkFunc(f1);

    cout << "f2 :";
    checkFunc(f2);

    cout << "f1 :";
    if(f1) {
        std::cout << "Function is not empty\n";
        f1();
    } else {
        std::cout << "Function is not empty\n";
    }
    cout << "f2 :";
    if(f2) {
        std::cout << "Function is not empty\n";
        f2();
    } else {
        std::cout << "Function is not empty\n";
    }
    return 0;
}
