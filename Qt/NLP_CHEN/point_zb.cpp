#include "point_zb.h"
#include <math.h>
#include <QDebug>
#include <ctime>
#include <unistd.h>
#include <debug_log.h>
#include <exception>
#include <jsoncpp/json/json.h>
point_zb::point_zb()
{
    get_optimal_path();
}
void point_zb::get_point(double x1, double y1,double x2, double y2, double r)
{
    double current_x,c,current_y,d;
    current_x = 0;
    c = 3;
    current_y = 0;
    d = 2;
    //直线方程：y=kx+b；
    double k = (d-current_y)/(c-current_x);
    qDebug() << "k = "<<k;
    double b = current_y - current_x*k;
    qDebug() << "b = "<<b;
//    圆方程：(x-c)^2+(y-d)^2=r^2;
//    double x1,x2,y1,y2;//交点坐标
    double l,m,n;
    l = k*k + 1;
    m = 2*(b-d)*k - 2*c;
    n = c*c+(b-d)*(b-d)-r*r;

    x1 = (-m + sqrt(m*m-4*l*n))/(2*l);
    x2 = (-m - sqrt(m*m-4*l*n))/(2*l);
    y1=k*x1+b;
    y2=k*x2+b;
    if(current_x < c)
    {
        if(x1 < c)
        {
            qDebug()<<x1 << " "<< y1 ;
        }
        else
        {
            qDebug()<< x2 << " "<<y2;
        }
    }
    else
    {
        if(x1 > c)
        {
            qDebug()<<x1 << " "<< y1 ;
        }
        else
        {
            qDebug()<< x2 << " "<<y2;
        }
    }
//    if(fabs(k*c-d+b)/sqrt(k*k+b*b))
//    {
//    x1=(2*c-2*k*(b-d)+sqrt(pow((2*k*(b-d)-2*c),2)-4*(k*k+1)*((b-d)*(b-d)+c*c-r*r)))/(2*k*k+2);
//    x2=(2*c-2*k*(b-d)-sqrt(pow((2*k*(b-d)-2*c),2)-4*(k*k+1)*((b-d)*(b-d)+c*c-r*r)))/(2*k*k+2);
//    y1=k*x1+b;
//    y2=k*x2+b;
//    }
    qDebug()<<x1 << " "<< y1 << " "<< x2 << " "<<y2;
}
int point_zb::check_time()
{
    //判断时间间隔，如果超过10s，则去掉之前的所有数据

    //如果在10s之内，插入
    //如果插入数据大于3次则计算，时间相隔/次数 <= 3
#if 0
    time_t rawtime;
    struct tm *ptminfo;
    st_time t;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    t.hour = ptminfo->tm_hour;
    t.min = ptminfo->tm_min;
    t.sec = ptminfo->tm_sec;
    qDebug()<< "v_time_group size:"<<v_time_group.size();
    if(v_time_group.size() > 0)
    {
        qDebug()<<"v_time_group.size() > 0";
        int h = t.hour - v_time_group.end()->hour;
        int m = t.min - v_time_group.end()->min;
        int s = t.sec -v_time_group.end()->sec;
        qDebug()<< " time : "<<s + m*60 + h*60*60;
        if(s + m*60 + h*60*60 > 10)
        {
            qDebug()<<"v_time_group.clear();";
            v_time_group.clear();
            v_time_group.push_back(t);
        }
        else
        {
            qDebug()<<"s + m*60 + h*60*60 < 10";
            if(v_time_group.size() > 3)
            {

                qDebug()<<"v_time_group.size() > 3";
                int x = (t.hour - v_time_group.end()->hour)*3600 + (t.min - v_time_group.end()->min)*60 + (t.sec -v_time_group.end()->sec)/v_time_group.size();
                if(x < 3)
                {
                    qDebug()<<"x < 3 :"<<x;
                    v_time_group.clear();
                    return 0;
                }
                else
                {
                    qDebug()<<"x > 3 :"<<x;
                    return 1;
                }
            }
            else
            {
                qDebug()<<"v_time_group.size() < 3";
                v_time_group.push_back(t);
            }
        }
    }
    else
    {
        qDebug()<<"v_time_group.size() < 0";
        v_time_group.push_back(t);
    }
    return 1;
#else
        std::chrono::steady_clock::time_point cur_time_ = std::chrono::steady_clock::now();
        st_time time;
        time.now_time = cur_time_;
        LOG(INFO) << "start";
        if(v_time_group.size() > 0)
        {
            LOG(INFO) << "组大于1";
            if(spend_time(v_time_group.end()->now_time,cur_time_) > 1)
            {
                LOG(WARNING) << "最后一个时间大于1,清空";
                v_time_group.clear();
                v_time_group.push_back(time);
                return false;
            }
            else
            {
                LOG(WARNING) << "最后一个时间没有大于1";
                if(spend_time(v_time_group.begin()->now_time,cur_time_) > 3)
                {
                    LOG(ERROR) << "success";
                    v_time_group.clear();
                    return true;
                }
            }
        }
        else
        {
            LOG(INFO) << "追加";
            v_time_group.push_back(time);
        }
        LOG(ERROR) << "failed";
        return false;

#endif
#if 0
//    time_t now_time;
//    now_time = time(NULL);
//    qDebug()<<now_time;

    time_t cur_time_;
    cur_time_= time(NULL);
    qDebug()<<"cur time: " << cur_time_;
    st_time t;
    t.t = cur_time_;
    if(v_time_group.size() > 0)
    {
        qDebug()<<"value = " <<spend_time(v_time_group.begin()->t,cur_time_);
        qDebug()<<"size = "<<v_time_group.size();
        if(spend_time(v_time_group.begin()->t,cur_time_) > 5)
        {
            qDebug()<<"spend_time(v_time_group.begin() - cur_time_) > 5";
            v_time_group.clear();
            v_time_group.push_back(t);
        }
        else if(v_time_group.size()>4 && spend_time(v_time_group.begin()->t,cur_time_) <= 5)
        {
            qDebug()<<"spend_time(v_time_group.begin() - cur_time_) < 5 && size > 10";
            v_time_group.clear();
            return 0;
        }
        else
        {
            v_time_group.push_back(t);
        }
    }
    else
    {

        v_time_group.push_back(t);
    }
//    qDebug()<<"1";
    return 1;

#endif
}
#if 0
double point_zb::spend_time(time_t a, time_t b)
{
    return b-a;
}
#endif
double point_zb::spend_time(std::chrono::steady_clock::time_point start_time, std::chrono::steady_clock::time_point finish_time){
  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(finish_time - start_time);
  return time_span.count();
}


double point_zb::get_distance_point(double x,double y,double m,double n)
{
    double distance = sqrt((x-m)*(x-m) + (y-n)*(y-n));
    LOG(INFO) << "distance is +"<< distance;
    return distance;
}


///0000117
void point_zb::get_optimal_path()
{
    std::string path = "/home/cby/rsData/conf/guide/patrol_points.json";
    get_patrol_line(1,path);
    if(tourline_.size() <= 0)
        return;
    show_point_info();
    double sto_x,sto_y;
    double distance = 0;

    double ro_pose_x = 1.5;
    double ro_pose_y = 1.5;
    for(auto i = tourline_.begin(); i != tourline_.end();i++)
    {
        LOG(INFO) << (*i).x << "  "<<(*i).y;
        double x = (*i).x;
        double y = (*i).y;

        if(distance == 0)
        {
            distance = get_distance_point(ro_pose_x,ro_pose_y,x,y);
            sto_x = x;
            sto_y = y;
        }
        if(get_distance_point(ro_pose_x,ro_pose_y,x,y) < distance)
        {
            distance = get_distance_point(ro_pose_x,ro_pose_y,x,y);
            sto_x = x;
            sto_y = y;
        }
        if((*i).id != 0)
            break;
    }
    LOG(INFO) << "distance "<< distance;
    LOG(INFO) << "sto_x :" << sto_x << " sto_y :" << sto_y;
    delete_point_from_list(sto_x,sto_y);
    show_point_info();
}


bool point_zb::get_patrol_line(int id,std::string &filename)
{
    Json::Reader reader;
    Json::Value root;
    std::ifstream is;
    int line_num = 0;
    int total = 0;
    is.open(filename, std::ios::binary);
    if(!is.is_open())
    {
        return false;
    }
    try{
        if(reader.parse(is,root))
        {
            total = root["patrol_line"].size();
            if(total <= 0)
            {
                return false;
            }
            for(int i=0; i < total; i++)
            {
                if(id == root["patrol_line"][i]["line_name"].asInt())
                {
                    line_num = i;
                    break;
                }
            }
            total = root["patrol_line"][line_num]["point"].size();
            if(total <= 0)
            {
                return false;
            }
            for(int i = 0;i< total;i++)
            {
                TourPoint p;
                p.id = root["patrol_line"][line_num]["point"][i]["id"].asInt();
                p.x = root["patrol_line"][line_num]["point"][i]["x"].asFloat();
                p.y = root["patrol_line"][line_num]["point"][i]["y"].asFloat();
                p.wait_time = root["patrol_line"][line_num]["point"][i]["retent_time"].asFloat();
                p.name = root["patrol_line"][line_num]["point"][i]["name"].asString();
                tourline_.push_back(p);
            }
        }
        else
        {
            return false;
        }
    }catch(std::exception &e)
    {
        LOG(ERROR) << "exception "<< e.what();
    }
    return true;
}

void point_zb::show_point_info()
{
    for(auto i = tourline_.begin(); i != tourline_.end();i++)
    {
        LOG(INFO) << "x : " << (*i).x <<" y : "<< (*i).y ;
    }
}

void point_zb::delete_point_from_list(double x, double y)
{
    for(auto i = tourline_.begin(); i != tourline_.end();)
    {
        if(x == (*i).x && y == (*i).y)
        {
            LOG(INFO) << "delate "<<(*i).x <<" "<< (*i).y;
            tourline_.erase(i);
            break;
        }
        else
        {
            LOG(INFO) << "delate "<<(*i).x <<" "<< (*i).y;
            tourline_.erase(i);
        }
    }
}

