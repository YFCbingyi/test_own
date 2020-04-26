#include <iostream>
#include <algorithm>
 
void test1(void)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int div = 2;
    std::for_each(arr, arr + sizeof(arr) / sizeof(int), [div](int x)
    {
        if(x % div == 0)
            std::cout<<x<<" ";
    });
    std::cout << std::endl;
}

void test2(void)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int div = 2;
    std::for_each(arr, arr + sizeof(arr) / sizeof(int), [=](int x)
    {
        if(x % div == 0)
            std::cout<<x<<" ";
    });
    std::cout << std::endl;
}

int main() {
    test1();
    test2();
}
