#ifndef CONFIG_JSON_H
#define CONFIG_JSON_H

#include <vector>
#include <string>
using namespace std;
#define GETLINE_INIT_GUIST 1
#define GETALLINFOMATION 0
#define CONFFILE "/home/cby/rsData/conf/guide/patrol_points.json"

class Config_json
{
public:
    Config_json();
    struct Behavior
    {
        bool support_intercept; ///支持拦截
        bool support_approach;  ///支持趋近
        bool support_moveview;  ///支持移动观察
        bool support_autopush;  ///支持主动推送
        bool support_autonear;  ///支持主动靠近
    }st_behavior_;
    struct Regist
    {
        std::string face_require;
        double distance;
    }st_regist_;
    struct InterAction {
        std::string push_speech;
        std::string leave_speech;
        int show;
    }st_interact_;

    typedef struct
    {
        int follow;
        int expression;
        int show;
        int level;
        string push_speech;
    }st_MsgInfo;
    typedef struct
    {
        string name;
        int has_level;
        string leave_speech;
        st_MsgInfo view_msg;
    }st_ConfInfo;

    typedef vector<st_MsgInfo> g_MsgInfo;
    typedef vector<st_ConfInfo> g_ConfInfo;
    bool load_config();
    bool get_patrol_line(int id = 1);
private:
    bool init_observer_guist();
    bool read_information(string &filepath);
    bool get_information(g_MsgInfo &gr,const string &name);
    int check_type_level(string &name);
    void test_form();
    void test_wait(string &name,int max_level);
    void send_service(g_MsgInfo &st,int level = 0);
    void send_voice(string &vi);
    int get_random_number(int max_num);
    void read_keyfile(std::string &robot_id);


    st_ConfInfo st_confinfo;
    g_ConfInfo g_confinfo;

    ///debug演示
public:
    bool get_debug(){return m_isdebug;}
    void set_isdebug(){m_isdebug = true;}
    void set_isNotdebug(){m_isdebug = false;}
private:
    bool m_isdebug;
    ///debug演示 cby -2019-04-11

};

#endif // CONFIG_JSON_H
