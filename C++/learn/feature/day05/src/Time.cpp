#include "Time.h"

#include <iostream>
using namespace std;
MyTime::MyTime(/* args */)
{
    cout << "MyTime::MyTime()" << endl;
}

MyTime::~MyTime()
{
}

MyTime& MyTime::operator=(const MyTime& time) {
    this->t = time.t;
    cout << "调用复制运算符" << endl;
    return *this;
}