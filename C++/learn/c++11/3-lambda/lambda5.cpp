/*************************************************************************
	> File Name: lambda5.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年05月21日 星期四 15时42分20秒
 ************************************************************************/

#include<iostream>
#include <atomic>
#include <mutex>
#include <thread>
#include <condition_variable>

#include <functional>
#include <chrono>
#include <unistd.h>

using namespace std;

void a() {
    auto f = [&](){
        std::string msg = "good";
        return msg;
    };

    std::string msg = f();
    std::cout << msg << std::endl;
}
using namespace std::chrono;
class OmClock
{
public:
    typedef long long ll;
    typedef std::function<void()> timeoutCB;
    OmClock(int msec, timeoutCB cb = timeoutCB()) : msec_(msec),timeout_cb_(cb), terminate_(false),allow_(false) {
        std::cout << "Omclock" << std::endl;
    }
    
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
            if(duration() > msec_) {
                timeout_cb_();
                allow_ = false;
                break;
            }
        }    
    }
    ll duration() {
        return duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - begin_).count();
    }
private:
    int msec_;
	timeoutCB timeout_cb_;
    std::thread time_thd;    
    std::atomic<bool> terminate_;
    time_point<high_resolution_clock> begin_;
    std::atomic<bool> allow_;
};


class B{
public:
    B(){}
    ~B(){}


    bool b() {
        
        auto f = [this]() -> bool {this->get_b(); 
                                   return true;};
        return has_b() ? f() : false ;
    }

    bool has_b() {
        return false;
    }

    void get_b(){
        std::string name = "get map";
        std::cout << name << std::endl;
    }

    void c() {
        terminate_ = false;
        timer_ptr_ = std::make_shared<OmClock>(1500, std::bind(&B::movetimeout, this));
        timer_ptr_->start();
    }
    
    void movetimeout()
    {
        std::cout << "timeout" << std::endl;
        terminate_ = true;
    }

    bool stop() {
        return terminate_;
    }

private:
    std::shared_ptr<OmClock> timer_ptr_;
    std::atomic<bool> terminate_;
};



int main() {

    B *b = new B;
    b->c();

    while(!b->stop()){
        sleep(1);
    }
    delete b;
    return 0;
}
