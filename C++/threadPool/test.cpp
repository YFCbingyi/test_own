/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 12时41分04秒
 ************************************************************************/

#include<iostream>
#include <chrono>
#include "ThreadPool.h"
using namespace std;

void func() {
	std::cout << "work in thread " << std::this_thread::get_id() << std::endl;
}

void fun2(int x) {
	std::cout << "task "<< x << " work in thread "<< std::this_thread::get_id() << std::endl;
}

int main() {
	ThreadPool thread_pool(3);
	thread_pool.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	for(int i = 0; i < 100; i++) {
		thread_pool.appendTask(std::bind(fun2, i));
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	thread_pool.stop();

	return 0;
}