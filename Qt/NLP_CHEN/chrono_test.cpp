#include "chrono_test.h"
#include "debug_log.h"
#include <unistd.h>
chrono_test::chrono_test()
{
    thd_ = std::thread(&chrono_test::run, this);
    for(auto i = 0;i< 10;i++)
    {
        sleep(1);
        manage();
    }

}

void chrono_test::manage() {
    time.reset();
    thread_flag = true;
    LOG(INFO) << "发布 1 1";
}

void chrono_test::run() {
    thread_flag = false;
    while(true) {
        usleep(100);
        if(!thread_flag) {
            continue;
        }
        if(time.elapsed() > 1500) {
            LOG(INFO) << "发布 0 0  ";
            thread_flag = !thread_flag;
        }
    }
}
