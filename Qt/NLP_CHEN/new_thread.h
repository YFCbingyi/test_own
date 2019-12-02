#ifndef NEW_THREAD_H
#define NEW_THREAD_H

#include <thread>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

class new_thread
{
public:
    new_thread();
    ~new_thread();

    void run_();
private:
    int get_random_number(int min,int max) const {
        return rand() % static_cast<int>(max + 1 - min) + min;
    }
    void _func1_(std::string  &i);
    void _func3_();
    void _func2_();
    std::thread thread1;
    std::thread thread2;
    bool flag_,finished_;
};

#endif // NEW_THREAD_H
