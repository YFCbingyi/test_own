/***************************************************
@File Name : test.cpp
@Project : 
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-28 08:48:58
****************************************************/

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

using namespace std;

mutex tex;
condition_variable cv;

void sleep() {
    this_thread::sleep_for(chrono::seconds(2));
    cout << "send notify one" << endl;
    cv.notify_one();
    // cv.notify_all();
    cout << "send notify one finished" << endl;
}

int main(int argc,char **argv)
{
    thread t(&sleep);
    unique_lock<mutex> lock(tex);
    cv.wait(lock);

    cout << "clock is ok" << endl;        
    t.join();
    return 0;
}
