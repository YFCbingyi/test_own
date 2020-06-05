/*************************************************************************
	> File Name: operator.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月03日 星期三 18时00分10秒
 ************************************************************************/

#include<iostream>
using namespace std;

class A{
public:
    int operator()(int val) {
        return val > 0 ? val : -val;
    }
};

int main() {
    int i = -1;
    A a;
    cout << a(i) << std::endl;
}
