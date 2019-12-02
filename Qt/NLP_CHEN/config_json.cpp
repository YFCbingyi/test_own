#include "config_json.h"
#include "debug_log.h"
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
Config_json::Config_json()
{
}

bool Config_json::load_config() {
    LOG(INFO) << "1";
    Json::Reader reader;
    Json::Value root;
    std::ifstream is;
    int line_num = 0;
    int total = 0;
    std::string type = "approach";
    is.open("/home/cby/rsData/conf/patrol/behavior.json", std::ios::binary);
    LOG(INFO) << "1";
    if(!is.is_open())
    {
        LOG(INFO) << "1";
        return false;
    }
    LOG(INFO) << "1";
    try{
        if(reader.parse(is,root))
        {
            LOG(INFO) << "1";
            for(int i = 0; i < root.size(); i++) {
                LOG(INFO) << "1";
                if(root[i]["type"].asString().compare(type))
                    continue;
                LOG(INFO) << "1";
                st_behavior_.support_approach = root[i]["behavior"]["support_approach"].asBool() ? true : false;
                if(st_behavior_.support_approach) {
                    LOG(INFO) << " ture";
                }
                else {
                    LOG(INFO) << "false";
                }
                std::string text;
                int m = 0;
                st_regist_.distance = (m = root[i]["regist"]["distence"].asInt()) > 0 ? m : 0;
                st_regist_.face_require = (text = root[i]["regist"]["face_require"].asString()).empty() ? "" : text;
                st_interact_.push_speech = (text = root[i]["msg"][0]["push_speech"].asString()).empty() ? "" : text;
                LOG(INFO) << st_regist_.distance << "  " << st_regist_.face_require;
            }
        }
    } catch (exception &e) {
        LOG(ERROR) << e.what();
    }
}

void Config_json::read_keyfile(std::string &robot_id)
{
    std::cout << "start "<< std::endl;
    std::string file = "/home/cby/.RS/license.key";
    ifstream is(file.c_str());
    std::string s;
//    if(is.is_open())
//    {
//        char *str;
//        is.getline(str,256);
//        std::cout << "str is "<<str << std::endl;
//    }
    while(getline(is,s))
    {
        robot_id+=s;
        std::cout << "str is "<<s << std::endl;
    }
    std::cout << "str is "<<robot_id << std::endl;
}

bool Config_json::get_patrol_line(int id)
{
    Json::Reader reader;
    Json::Value root;
    std::ifstream is;
    int line_num = 0;
    int total = 0;
    is.open("/home/cby/rsData/conf/patrol/routers.json", std::ios::binary);
    if(!is.is_open())
    {
        return false;
    }
    try{
        if(reader.parse(is,root))
        {
            if(root["is_debug"].asBool())
            {
                LOG(INFO) << " ture";
            }
            else
            {
                LOG(INFO) << " false";
            }
        }
        else
        {
            return false;
        }
    }catch(std::exception &e)
    {
        LOG(ERROR) << e.what();
    }
    return true;
}

bool Config_json::init_observer_guist()
{
    Json::Reader reader;
    Json::Value root;
    std::ifstream is;
    int total = 0;
    is.open("/home/cby/rsData/conf/guide/observer_config.json", std::ios::binary);
    if(!is.is_open())
    {
        return false;
    }
    try{
        if(reader.parse(is,root))
        {
            total = root["regions"].size();

            if(total <= 0)
            {
                return false;
            }
            for(int i=0; i < total; i++)
            {
//                std::string name = root["regions"][i]["name"].asString().substr(0,4);
                std::string real_name = root["regions"][i]["name"].asString();
                std::string name = real_name.substr(0,4);
                std::string id = real_name.substr(real_name.length()-1,real_name.length());
                int i_id = atoi(id.c_str());
                LOG(INFO) << "name is "<< name << "   id  " << id << "i_id+1 is "<<i_id;
                if(name.compare("form") == 0)
                {
                    LOG(INFO) << "[form] real name is :"<< root["regions"][i]["name"].asString();
                }
                else if(name.compare("wait") == 0)
                {
                    LOG(INFO) << "[wait] real name is :"<< root["regions"][i]["name"].asString();
                }
                else if(name.compare("rela") == 0)
                {
                    LOG(INFO) << "[rela] real name is :"<< root["regions"][i]["name"].asString();
                }
                else if(name.compare("coun") == 0)
                {
                    LOG(INFO) << "[coun] real name is :"<< root["regions"][i]["name"].asString();
                }
            }
        }
        else
        {
            return false;
        }
    }catch(std::exception &e)
    {
        LOG(ERROR) << e.what();
    }
    return true;
}

bool Config_json::read_information(string &filepath)
{
    Json::Reader reader;
    Json::Value root;
    std::ifstream is;
    st_ConfInfo st_area_view;
    is.open(filepath, std::ios::binary);
    if(!is.is_open())
    {
        return false;
    }
    try{
        if(reader.parse(is,root))
        {
            int view_cost = root["area_view"].size();
            LOG(ERROR) << "view_cost is "<<view_cost;
            for(int i = 0; i != view_cost; i++)
            {
                int msg_cost = root["area_view"][i]["msg"].size();
                LOG(INFO) << "msg_cost is "<<msg_cost << "  i = "<<i;
                for(int j = 0; j != msg_cost; j++)
                {
//                    memset(st_area_view,0,sizeof(st_area_view));
                    st_area_view.name = root["area_view"][i]["name"].asString();
                    st_area_view.view_msg.show = root["area_view"][i]["msg"][j]["show"].asInt();
                    st_area_view.view_msg.push_speech = root["area_view"][i]["msg"][j]["push_speech"].asString();
                    st_area_view.leave_speech = root["area_view"][i]["leave_speech"].asString();
                    g_confinfo.push_back(st_area_view);
                }
            }
        }
    }catch(std::exception &e)
    {
        LOG(ERROR) << e.what();
    }
    return true;
}

int Config_json::check_type_level(string &name)
{
    for(auto it = g_confinfo.begin(); it != g_confinfo.end(); it ++)
    {
        if((*it).name.compare(name) == 0)
        {
            if((*it).has_level)
                return (*it).has_level;
        }
    }
    return 0;
}

void Config_json::test_form()
{

}

void Config_json::test_wait(string &name,int max_level)
{
    g_MsgInfo wait_info;
    get_information(wait_info,name);
    LOG(INFO) << " expression "<< wait_info[0].expression
              << " follow "<<wait_info[0].follow
              << " push_speech "<<wait_info[0].push_speech
              << " show "<<wait_info[0].show;
    LOG(INFO) << "wait_info size "<<wait_info.size();
    if(max_level != 0)
    {
        send_service(wait_info,1);
    }
    else
    {
        send_service(wait_info);
    }


}

bool Config_json::get_information(g_MsgInfo &gr,const string &name)
{
    st_MsgInfo st;

    LOG(INFO) << "get information";
    for(auto it = g_confinfo.begin(); it != g_confinfo.end(); it ++)
    {
        LOG(INFO) << "+++ "<<(*it).name;
        if((*it).name.compare(name) == 0)
        {
            st.expression = (*it).view_msg.expression;
            st.follow = (*it).view_msg.follow;
            st.push_speech = (*it).view_msg.push_speech;
            st.level = (*it).view_msg.level;
            st.show = (*it).view_msg.show;
            gr.push_back(st);
            LOG(INFO) << "push back ...";
        }
    }

}

void Config_json::send_service(g_MsgInfo &st,int level)
{
    g_MsgInfo ss;
    st_MsgInfo info;

    for(auto is = st.begin();is != st.end();is++)
    {
        if((*is).level == level)
        {
            info.expression = (*is).expression;
            info.follow = (*is).expression;
            info.push_speech = (*is).push_speech;
            info.show = (*is).show;
            ss.push_back(info);
        }
    }
    int ss_size = ss.size();
    LOG(INFO) << "ss_size is : "<<ss_size;
    //获取随机数 i = 1;
    int list_num = get_random_number(ss_size);
    switch (ss[list_num].show) {
    case 1:
        LOG(WARNING) << "显示首页";
        break;
    case 2:
        LOG(WARNING) << "显示中心导览";
        break;
    case 3:
        LOG(WARNING) << "显示业务咨询";
        break;
    case 4:
        LOG(WARNING) << "显示表格模板";
        break;
    default:
        break;
    }

    send_voice(ss[list_num].push_speech);

}

void Config_json::send_voice(string &vi)
{
    string str = vi;
    string speech;
    string sub = "///";
    int num = 0;
    for (size_t i=0; (i=str.find(sub,i)) != std::string::npos; num++, i++);
    if(num == 0)
    {
        speech = str;
        LOG(INFO) << "only speech is " << speech;
        return ;
    }
    LOG(INFO) << " num : "<<num;
    LOG(INFO) << "有 "<<num+1 <<" 句话";
    int rande = get_random_number(num+1)+1;
    int count = 0;
    int begin = -1;
    for(int i = 0 ; i < num ;i++)
    {
        while((begin=str.find(sub,begin+1))!=string::npos)
        {
            speech = str.substr(0,begin);
            str = str.substr(begin+3,str.length());
        }
        count++;
        if(rande == count)
            LOG(INFO) << "就是这句话 "<<speech;
    }
    count++;
    speech = str;
    if(rande == count)
        LOG(INFO) << "就是这句话 "<<speech;

}

int Config_json::get_random_number(int max_num)
{
    srand(time(0));
    return rand()%max_num;
}
