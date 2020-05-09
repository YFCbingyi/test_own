/*************************************************************************
	> File Name: CountDown.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月09日 星期六 16时44分43秒
 ************************************************************************/

#ifndef _COUNTDOWN_H
#define _COUNTDOWN_H

#include <iostream>
#include <atomic>
#include <future>

class CountDown
{
private:
	/* data */
	std::atomic<bool> timeout_;
	
public:
	CountDown(/* args */);
	~CountDown();

	bool IsTimeout() {return timeout_;}
};

#endif
