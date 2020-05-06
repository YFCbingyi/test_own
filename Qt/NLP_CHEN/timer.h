#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <unistd.h>

using namespace std::chrono;
typedef long long ll;
class OmClock
{
public:
    typedef std::function<void()> timeoutCB;
    OmClock(int msec, timeoutCB cb = timeoutCB()) : msec_(msec),timeout_cb_(cb), terminate_(false),allow_(false) {}
    
    void start() {
        restart();
        time_thd = std::thread(&OmClock::run,this);
    }
    void restart() {
        allow_ = true;
        std::cout << "restart "<< std::endl;
        begin_ = high_resolution_clock::now();
    }
    void stop() {
        terminate_ = true;
        if(time_thd.joinable())
            time_thd.join();
    }
    
    void run() {
        while(!terminate_) {
            sleep(1);
            if(!allow_)
                continue;
            if(duration() > 4500) {
                timeout_cb_();
                allow_ = false;
                break;
            }
        }    
    }
    ll duration() {
        duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - begin_).count();
    }
private:
    int msec_;
	timeoutCB timeout_cb_;
    std::thread time_thd;    
    std::atomic<bool> terminate_;
    time_point<high_resolution_clock> begin_;
    std::atomic<bool> allow_;
};

#endif // TIMER_H