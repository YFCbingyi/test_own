#ifndef MY_TEMPLATE_H
#define MY_TEMPLATE_H
#include <iostream>
#include "testbase.h"

class my_template : public TestBase
{
public:
    my_template();
    void test() {}
    void run();

private:
    template<typename T> void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }
};

#endif // MY_TEMPLATE_H
