#ifndef MY_THREAD_H
#define MY_THREAD_H
#include <thread>
#include <iostream>
#include <future>

using namespace std;
class my_thread
{
public:
    my_thread();
    void start();
private:
    enum status_{
        NORMAL,
        TERMINATE,
    };
    void run(std::promise<int>& promise_obj);
private:
    thread thd_;
};

#endif // MY_THREAD_H
