#include <functional>
#include <iostream>

void f0(int i) { std::cout << "lvalue ref: " << i << ", \t" << &i << "\n"; }
void f1(int& i) { std::cout << "lvalue ref: " << i << ", \t" << &i << "\n"; }
void f2(int&& i) { std::cout << "rvalue ref: " << i << ", \t" << &i << "\n"; }

int main()
{
    int i = 77;
    f1(i);    // lvalue ref called
    //f1(9);
    f2(std::move(i));

    f0(99);
    f2(199);   // rvalue ref called

    int&& rvalue_ref = 299;
    f0(rvalue_ref);

    return 0;
}
