#include "my_resolver.h"

#include <iostream>
my_resolver::my_resolver() : aaa(1)
{

}

void f() {
    std::cout << "globel "<< std::endl;
}
int aaa;
void my_resolver::f() {
    ::f();
    aaa++;
    std::cout << "this aaa "<< aaa;
    ::aaa = 10;
    std::cout << "::aaa "<<::aaa;
}
