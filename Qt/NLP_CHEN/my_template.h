#ifndef MY_TEMPLATE_H
#define MY_TEMPLATE_H
#include <iostream>
using namespace std;
class my_template
{
public:
    my_template();
    void run();

private:
    template<typename T> void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }
};

#endif // MY_TEMPLATE_H
