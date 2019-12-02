#include "xunshi.h"
#include <pthread.h>
#include <QDebug>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include "debug_log.h"

xunshi::xunshi()
{
    set_id(5);
}

bool xunshi::get_next_node(st_msg &msg)
{
    return true;
}

void* xunshi::move_func_(void *ptr)
{
    qDebug()<< ((xunshi*)ptr)->msg.x <<((xunshi*)ptr)->msg.y;
    int i = 0;
    while(true)
    {
        sleep(1);
        i++ ;
        if(i == 5)
            break;
    }
    ((xunshi*)ptr)->move_finished = true;
}

void* xunshi::view_func_(void *ptr)
{

    int i = 0;
    while(true)
    {
        sleep(1);
        i++ ;
        if(i == 5)
            break;
    }
    ((xunshi*)ptr)->view_finished = true;
}

void xunshi::set_value(int i)
{
    if(i ==1)
        move_finished = true;
    if(i ==2)
        view_finished = true;
}
void xunshi::run()
{
    std::string l = "gogogog";
    show_msg(l);
#if 0
    start_ = false;
    view_finished = false;
    move_finished = false;
    time_t timeBegin = time(0);
    while(1)
    {
        //get point info
        usleep(100);
        if(time(0) - timeBegin >= 50)
        {
            break;
        }
        if(!start_)
        {
            qDebug() << "开始";
            msg.id = 1;
            msg.x = -0.987;
            msg.y = 0.0485;
            start_ = true;
            pthread_t thd_move_;
            pthread_create(&thd_move_,NULL,move_func_,(void*)this);
        }
        if(move_finished)
        {
            qDebug() << "移动完成";
            move_finished = false;
            if(msg.id != 0)
            {
                msg.id = 0;
                qDebug() << "非观察点，移动";
                pthread_t thd_move_;
                pthread_create(&thd_move_,NULL,move_func_,(void*)this);
            }
            else
            {
                qDebug() << "观察点，观察";
                pthread_t thd_view_;
                pthread_create(&thd_view_,NULL,view_func_,(void*)this);
            }
        }

        if(view_finished)
        {
            qDebug() << "观察完成,移动";
            view_finished = false;
            pthread_t thd_move_;
            pthread_create(&thd_move_,NULL,move_func_,(void*)this);
        }
    }
    qDebug()<< "结束";
#endif
}

bool xunshi::get_area_msg()
{
    Json::Reader reader;
    Json::Value root;
    std::ifstream is;
    int line_num = 0;
    int type_cost = 0;
    is.open("/home/cby/rsData/conf/patrol_points.json", std::ios::binary);
    if(!is.is_open())
    {
        return false;
    }
    try{
        if(reader.parse(is,root))
        {
            type_cost = root["area_view"].size();
            LOG(INFO) << "区域类型一共有 "<<type_cost << " 个";
            for(int i = 0; i != type_cost;i++)
            {
                std::string type_msg = root["area_view"][i].toStyledString();
                set_every_area_msg(type_msg);
            }
        }
    }catch(std::exception &e)
    {
        LOG(ERROR) << "exception : "<<e.what();
    }
}

void xunshi::show_msg(std::string msg)
{
    LOG(INFO) << msg;
}

bool xunshi::set_every_area_msg(std::string &str_)
{
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str_,DevJson);
    int leave_cost,push_cost,msg_cost;
    st_regionType_msg st_form;
    msg_cost = DevJson["msg"].size();
    LOG(INFO) << "msg 个数 "<<msg_cost;
    for(int i=0;i != msg_cost;i++)
    {
        push_cost = DevJson["msg"][i]["push_speech"].size();
        LOG(INFO) << "push_speech 个数 "<<push_cost;
        for(int j=0;j!=push_cost;j++)
        {
            st_form.push_speech.push_back(DevJson["msg"][i]["push_speech"][j].asString());
        }
        st_form.expression = DevJson["msg"][i]["expresstion"].asInt();
        st_form.follow = DevJson["msg"][i]["follow"].asInt();
        st_form.show = DevJson["msg"][i]["show"].asInt();
        leave_cost = DevJson["msg"][i]["leave_speech"].size();
        for(int j=0;j!=leave_cost;j++)
            st_form.leave_speech.push_back(DevJson["msg"][i]["leave_speech"][j].asString());
    }
    LOG(INFO) << "push_speech "<<st_form.push_speech.size();
    for(int i=0;i != push_cost;i++)
    {
        std::string pop_speech = st_form.push_speech[i];
        LOG(INFO) << "pop speech "<<pop_speech;
    }
    for(int i=0;i != leave_cost;i++)
    {
        std::string leave_speech = st_form.leave_speech[i];
        LOG(INFO) << "leave speech "<<leave_speech;
    }
//    if(!DevJson["name"].asString().compare("form"))
//    {
//    }
//    else if(!DevJson["name"].asString().compare("counter"))
//    {
//        LOG(INFO) << "当前的区域是 " <<str_;
//    }
//    else if(!DevJson["name"].asString().compare("wait"))
//    {
//    }
//    else if(!DevJson["name"].asString().compare("relax"))
//    {
//    }
}
