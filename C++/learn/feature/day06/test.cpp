/***************************************************
@File Name : test.cpp
@Project : 
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-09-08 17:20:23
****************************************************/

#include <iostream>
#include <thread>

using namespace std;

int main(int argc,char **argv)
{
    for(int i = 0; i < 3 ; i++) {
    bool tem = false;
    
    std::thread t([&]{
        while (!tem)
        {
            std::cout << boolalpha << "tem  is " << tem << std::endl;
        }
        std::cout << boolalpha << "tem  is " << tem << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    tem  = true;
    std::cout << boolalpha << "tem  is change " << tem << std::endl;
    if(t.joinable())
        t.join();

    }
    return 0;
}
