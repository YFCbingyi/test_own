#ifndef MYBIND_H
#define MYBIND_H
#include <functional>
#include <jsoncpp/json/json.h>

class mybind
{
public:
    typedef std::function<void(const std::string& text,Json::Value &res)> ShowListenCB;
    typedef std::function<void(const std::string&)> ShowStringCB;
    typedef std::function<void(const Json::Value&)> ShowJsonCB;
    typedef std::function<void()> TimeOutCB;
    static mybind* getInstance(
            ShowListenCB cb_ = ShowListenCB()) {

        if(instance_ == NULL)
            instance_ = new mybind(cb_);

        return instance_;
    }
    void run();
    void regist_string_ontime_cb(ShowStringCB cb) {show_string = cb;}
    void regist_Json_ontime_cb(ShowJsonCB cb){show_json = cb;}
    void regist_time(TimeOutCB cb) {time_out_ = cb;}
private:
    mybind(ShowListenCB cb_);
    ~mybind();
    static mybind* instance_;
    ShowListenCB show_listen;
    ShowStringCB show_string;
    ShowJsonCB show_json;
    TimeOutCB time_out_;
};

#endif // MYBIND_H
