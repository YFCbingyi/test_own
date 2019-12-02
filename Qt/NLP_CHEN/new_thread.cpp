#include "new_thread.h"
#include "debug_log.h"
#include <exception>
#include <pthread.h>
#include<signal.h>
#include <condition_variable>
#include <mutex>

std::mutex mt;
std::condition_variable cond;
bool flag;
new_thread::new_thread()
{
    flag = true;
}

new_thread::~new_thread()
{
//    pthread_kill(thread1.get_id(),SIGQUIT);
//    thread1.join();
    thread2.join();
}

void new_thread::run_()
{
    LOG(INFO) << "run _ ";
    std::string al = "sfja";
    int i = 20;
//    while(i--)
    {
        try
        {
            flag_ = false;
            finished_ = false;
//            thread1 = std::thread(&new_thread::_func1_, this,std::ref(al));
            thread2 = std::thread(&new_thread::_func3_, this);
        }
        catch(std::exception &e)
        {
            LOG(ERROR) << "exception: "<< e.what();
        }
    }
}

void new_thread::_func1_(std::string  &i)
{
    while(true)
    {
        if(flag) {
            std::unique_lock<std::mutex> lck(mt);
            cond.wait(lck);
            flag = false;
        } else {

        }
        sleep(1);
        LOG(INFO) << "erer";
    }
}

void new_thread::_func2_()
{
    int i = 1;
    while (true)
    {
        sleep(2);
        i++;
        LOG(INFO) << i;
        if((i % 5) == 0) {
            std::unique_lock<std::mutex> lck(mt);
            cond.notify_one();
        } else if(i == 7){
            flag = true;
        }

    }
}
#if 1
void new_thread::_func3_()
{
    while(true)
    {
        usleep(100);
//        int a =
        LOG(INFO) << get_random_number(0,4);
    }
}

#endif
