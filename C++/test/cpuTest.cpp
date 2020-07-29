
#include<stdio.h>
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include<stdlib.h>

using namespace std;

typedef long long int int64;
const int NUM_THREADS = 4; //CPU core nums
int INTERVAL = 100;
int cpuinfo = 15; //CPU utilization rate

// time unit is "ms"
int64 GetTickCount()
{
    timespec now;
    int64 sec, nsec;

    clock_gettime(CLOCK_MONOTONIC, &now);
    sec = now.tv_sec;
    nsec = now.tv_nsec;

    return sec * 1000 + nsec / 1000000;
}

void* CPUCost(void *args)
{
    int busyTime = INTERVAL * cpuinfo / 100;
    int idleTime = INTERVAL - busyTime;
    int64 startTime = 0;

    while (true) {
        startTime = GetTickCount();
        while((GetTickCount() - startTime) <= busyTime);
        usleep(idleTime * 1000);
    }
}

int main(int argc, char **argv)
{
    pthread_t t[NUM_THREADS];
    int ret;
    if(argc != 2) {
        std::cout << "wrong format, please input : cpuTest [0~100] " << std::endl;
        return -1;
    }
    string rate = argv[1];
    cpuinfo = std::stoi(rate);
    if(cpuinfo < 0 || cpuinfo > 100) {
        std::cout << "wrong format, please input : cpuTest [0~100] " << std::endl;
        return -1;
    }
    for(int i = 0; i < NUM_THREADS; i++) {
        ret = pthread_create(&t[i], NULL, CPUCost, NULL);
        if(ret)
            std::cout << "XXXX create err" << std::endl;
    }

    pthread_exit(NULL);
    return 0;
} 
