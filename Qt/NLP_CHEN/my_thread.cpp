#include "my_thread.h"
#include "debug_log.h"
#include <chrono>
#include <unistd.h>
my_thread::my_thread()
{

}

void my_thread::start() {
    std::promise<int> promise_obj;
    std::future<int> future_obj = promise_obj.get_future();
    thd_ = thread(&my_thread::run,this,std::ref(promise_obj));
    while(future_obj.wait_for(std::chrono::milliseconds(1000)) == std::future_status::timeout) {
        LOG(INFO) << "heartbeat ";
    }
    int status = future_obj.get();
    if(status == NORMAL) {
        LOG(INFO) << "normal over";
    } else if(status == TERMINATE) {
        LOG(INFO) << "terminate over";
    } else {
        LOG(ERROR) << "It's a question";
    }
    if(thd_.joinable())
        thd_.join();
}

void my_thread::run(std::promise<int> &promise_obj) {
    int a = 10;
    while (true) {
        ::sleep(2);
        LOG(INFO) << "run ...";
        a--;
        if(a == 0)
            break;
    }
    promise_obj.set_value(TERMINATE);
}
