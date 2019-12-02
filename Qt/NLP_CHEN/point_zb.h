#ifndef POINT_ZB_H
#define POINT_ZB_H
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <string>

class point_zb
{
public:

    typedef struct {
      std::string speech;
      int id;
      int func_id;
      double x;
      double y;
      double wait_time;
      ///0000149
      std::string name;
      ///0000149 cby -2019-04-04
    } TourPoint;

    typedef std::vector<TourPoint> TourLine;

    typedef struct
    {
        std::chrono::steady_clock::time_point now_time;
    }st_time;
    typedef std::vector<st_time> TimeGroup;

    TimeGroup v_time_group;
    point_zb();
    void get_point(double x1, double y1,double x2, double y2, double r);
    int check_time();
//    double spend_time(time_t a,time_t b);
    double spend_time(std::chrono::steady_clock::time_point start_time, std::chrono::steady_clock::time_point finish_time);

    TourLine tourline_; //存放点的信息集合
    void get_optimal_path();
    double get_distance_point(double x,double y,double m,double n);
    bool get_patrol_line(int id,std::string &filename);
    void show_point_info();
    void delete_point_from_list(double x,double y);

};

#endif // POINT_ZB_H
