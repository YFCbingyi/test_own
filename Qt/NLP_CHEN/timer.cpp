#include "timer.h"
#include "debug_log.h"
#include <unistd.h>
//Timer::Timer() : terminate_(false)
//{
    
//}

//void Timer::start() {
//    restart();
//    time_thd = std::thread(&Timer::run,this);
//}


//void Timer::stop() {
//    terminate_ = true;
//    if(time_thd.joinable())
//        time_thd.join();
//}

//void Timer::run() {
//    while(!terminate_) {
//        sleep(1);
//        std::cout << "dur "<<duration() << std::endl;
//        if(duration() > 4500) {
//            LOG(INFO) << "OK";
//            break;
//        }
//    }    
//}