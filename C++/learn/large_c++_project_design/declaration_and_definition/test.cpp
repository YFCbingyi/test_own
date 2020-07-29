/*************************************************************************
	> File Name: test.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年07月14日 星期二 11时08分31秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*
* 在一个给定的作用域中：
* 重复一个声明是合法的，
* 在程序中使用的每个实体必须只有一个定义*/

int f(int,int);
int f(int,int);
typedef int uint_32;
typedef int uint_32;
extern int global;
extern int global;

class NoGood{
    static int i;
    //static int i;//
public:
    int f();
    //int f();//
};

int main() {
    
    return 0;
}
