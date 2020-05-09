#ifndef _THREADBASE_H_
#define _THREADBASE_H

#include <thread>

class ThreadBase
{
private:
    /* data */

public:
    ThreadBase(/* args */) : terminate(false) {}
    ~ThreadBase() { stop(); }

    void start() { thd_ = std::thread(&ThreadBase::run, this); }
    void stop()
    {
        terminate = true;
        if (thd_.joinable())
            thd_.join();
    }
    virtual void run() = 0;
    std::thread thd_;
    bool terminate;
};
#endif