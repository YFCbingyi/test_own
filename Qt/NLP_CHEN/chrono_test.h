#ifndef CHRONO_TEST_H
#define CHRONO_TEST_H

#include <iostream>
#include <chrono>
#include <thread>
//#define ll long long

using namespace std;
using namespace std::chrono;

class Timer{
public:
    Timer() : m_begin(high_resolution_clock::now()) {}
    //重置当前时间
    void reset() {
        m_begin = high_resolution_clock::now();
    }

    //默认输出毫秒
    double elapsed() const {
        return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
    }

    //微秒
    double elapsed_micro() const {
        return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
    }

    //纳秒
    double elapsed_nano() const {
        return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
    }

    //秒
    double elapsed_seconds() const {
        return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
    }

    //分
    double elapsed_minutes() const {
        return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
    }

    //时
    double elapsed_hours() const {
        return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
    }

private:
    time_point<high_resolution_clock> m_begin;

};

using namespace std;
class chrono_test
{
public:
    chrono_test();

private:
    void manage();
    void run();
private:
    Timer time;
    std::thread thd_;
    bool thread_flag;
};

#endif // CHRONO_TEST_H
