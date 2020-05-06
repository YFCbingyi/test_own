#ifndef MY_RESOLVER_H
#define MY_RESOLVER_H

#include "testbase.h"
class my_resolver : public TestBase
{
public:
    my_resolver();
    
    void test() {
        this->f();                
    }
    void f();

private:
    int aaa;
};

#endif // MY_RESOLVER_H
