#ifndef MY_JSON_H
#define MY_JSON_H

#include <iostream>
#include <jsoncpp/json/json.h>
#include "testbase.h"

class my_json : public TestBase
{
public:
    my_json();
    void test() {
        Json::Value root = create_json();
    }
    
private:
    void create_json(std::string &path); 
    Json::Value create_json(); 
private:
    struct Subject{
        std::string item;
        std::vector<std::string> option;
        std::vector<std::string> answer;
        int time_count;
    };
    struct Script {
        int subject_num;
        int alarm;
        std::string QRcode;
        std::string error_speak;
        std::string right_speak;
        std::vector<Subject> subjects;
    };
    Script script_;
    bool init_script(const std::string& path);
private:
    Json::Value param() {
        Json::Value root;
        root["name"] = "patrol";
        root["value"] = 1;
        return root;
    }
};

#endif // MY_JSON_H
