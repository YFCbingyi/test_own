#include <iostream>
#include <string>
#include <thread>

// By default all arguments are copied into the internal storage of new thread.
void threadCallback(int x, std::string str)
{
    std::cout<<"Passed Number = "<<x<<std::endl;
    std::cout<<"Passed String = "<<str<<std::endl;
}

int main()  
{
    float x = 10.09;
    std::string str = "Sample String";
    
    std::thread th(threadCallback, x, str);

    th.join();
    return 0;
}
