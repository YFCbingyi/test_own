/*************************************************************************
	> File Name: ThreadPool.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 12时21分57秒
 ************************************************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

class ThreadPool
{
public:
	using Task = std::function<void()>;

	explicit ThreadPool(int size) : _thread_num(size), _is_running(false) {}
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool& other) = delete;
	~ThreadPool()
	{
		if (_is_running)
			stop();
	}
	void start()
	{
		_is_running = true;
		for (int i = 0; i < _thread_num; i++)
			_threads.emplace_back(std::thread(&ThreadPool::work, this));
	}
	void stop()
	{
		{
			std::unique_lock<std::mutex> lk(_mtx);
			_is_running = false;
			_cond.notify_all();
		}
		for(std::thread& t : _threads) {
			if(t.joinable())
				t.join();
		}
	}
	void appendTask(const Task& task) {
		if(_is_running) {
			std::unique_lock<std::mutex> lk(_mtx);
			_tasks.push(task);
			_cond.notify_one();
		}
	}
private:
	void work() {
		printf("begin work thread %d\n",std::this_thread::get_id());
		while (_is_running)
		{
            Task task;
            std::unique_lock<std::mutex> lk(_mtx);
            if(!_tasks.empty()) {
                task = _tasks.front();
                _tasks.pop();
            } else if (_is_running && _tasks.empty()) {
                _cond.wait(lk);
            }
            if(task)
				task();
		}
		printf("end work thread %d\n",std::this_thread::get_id());	
	}

private:
	std::atomic_bool _is_running;
	std::mutex _mtx;
	std::condition_variable _cond;
	int _thread_num;
	std::vector<std::thread> _threads;
	std::queue<Task> _tasks;
};

#endif
