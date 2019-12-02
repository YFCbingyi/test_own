#ifndef MY_TIME_H
#define MY_TIME_H
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>

class my_time
{
public:
    my_time();
    void start() {
        init(5);
        plan_list_index_ =  get_plan_list_index();
        std::cout <<" index " <<plan_list_index_ << std::endl;
    }

private:
    int get_plan_list_index() {
        int i =0;
        for(; i < plan_list_.size(); i++) {
            time_t now = time(0);
            tm *Itm = localtime(&now);
            std::cout << "当前时间: "<< Itm->tm_hour << ":" << Itm->tm_min << ":" << Itm->tm_sec << std::endl;
            std::cout << "计划时间: "<< plan_list_[i].time.hour << ":" << plan_list_[i].time.min << ":" << plan_list_[i].time.sec << std::endl;
            if(Itm->tm_hour > plan_list_[i].time.hour) {

            } else if(Itm->tm_hour >= plan_list_[i].time.hour && Itm->tm_min > plan_list_[i].time.min) {

            } else if(Itm->tm_hour >= plan_list_[i].time.hour && Itm->tm_min >= plan_list_[i].time.min && Itm->tm_sec > plan_list_[i].time.sec) {

            } else {
                break;
            }
        }
        return i;
    }
    bool get_time_out() {
        time_t now = time(0);
        struct tm *t = localtime(&now);
        std::cout << "时间: "<< t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << std::endl;
        if(t->tm_hour >= st.time.hour && t->tm_min >= st.time.min && t->tm_sec > st.time.sec) {
            return true;
        }
        if(t->tm_hour >= st.time.hour && t->tm_min > st.time.min) {
            return true;
        }
        if(t->tm_hour > st.time.hour) {
            return true;
        }
        return false;
    }
    void init() {
        std::string str="14:55:10";
        get_time(str);
    }

    void init(int i) {
        struct execplan t;
        int x = 12;
        while (i--) {
            t.mode = "patrol";
            t.num = 1;
            t.time.hour = x++;
            t.time.min = 35;
            t.time.sec = 12;
            plan_list_.push_back(t);
        }
    }

    void get_time(std::string &str) {
        struct plan_time pl;
        std::string::size_type n;
        std::string hour;
        for(int i = 0; i < 3; i++){
            n = str.find(":");
            if(n != std::string::npos) {
                hour = str.substr(0,n);
                std::cout << "hour "<< hour << " " << str.length()<< std::endl;
                str = str.substr(n+1,str.length());
            } else {
                hour = str;
                std::cout << "hour "<< hour << " " << str.length()<< std::endl;
            }
            if(i == 0) {
                pl.hour = std::stoi(hour);
            } else if(i == 1) {
                pl.min = std::stoi(hour);
            } else if(i == 2) {
                pl.sec = std::stoi(hour);
            }
        }
        std::cout << "plan time "<< pl.hour << pl.min << pl.sec << std::endl;
    }
    struct plan_time{
        int hour;
        int sec;
        int min;
    };
    struct execplan
    {
        std::string mode;
        int num;
        struct plan_time time;
    };
    struct execplan st;
    std::vector<struct execplan> plan_list_;
    int plan_list_index_;
};

#endif // MY_TIME_H
