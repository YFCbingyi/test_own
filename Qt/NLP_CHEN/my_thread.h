#ifndef MY_THREAD_H
#define MY_THREAD_H
#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>
#include <functional>
#include "testbase.h"
using namespace std;

class MyThreadPool
{
public:
    using Task =  std::function<void()>;
    explicit MyThreadPool(int num) : _threadNum_(num),_is_running_(false) {

    }
    ~MyThreadPool() {
        if(_is_running_)
            stop();
    }
    void start() {
        _is_running_ = true;
        for(int i = 0; i < _threadNum_; i++) {
            _threads_.emplace_back(std::thread(&MyThreadPool::work,this));
        }
    }
    void stop() {
        std::unique_lock<std::mutex> lk(_mtx_);
        _is_running_ = false;
        _cond_.notify_all();

        for(std::thread& t : _threads_) {
            if(t.joinable())
                t.join();
        }
    }
    void appendTask(const Task& task) {
        if(_is_running_) {
            std::unique_lock<std::mutex> lk(_mtx_);
            _tasks_.push(task);
            _cond_.notify_one();
        }
    }
public:
    MyThreadPool(const MyThreadPool&) = delete;
    MyThreadPool& operator = (const MyThreadPool& other) = delete;
private:
    void work() {
        std::cout << "begin  work thread: " << std::this_thread::get_id() << std::endl;
        while(_is_running_) {
            Task task;
            {
                std::unique_lock<std::mutex> lk(_mtx_);
                if(!_tasks_.empty()) {
                    task = _tasks_.front();
                    _tasks_.pop();
                } else if(_is_running_ && _tasks_.empty()) {
                    _cond_.wait(lk);
                }
            }
            if(task)
                task();
        }
        std::cout << "end work thread: "<<std::this_thread::get_id() << std::endl;
    }
private:
    std::atomic_bool _is_running_;
    std::mutex _mtx_;
    std::condition_variable _cond_;
    int _threadNum_;
    std::vector<std::thread> _threads_;
    std::queue<Task> _tasks_;
};

class my_thread : public TestBase
{
public:
    my_thread();
    void test();
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
