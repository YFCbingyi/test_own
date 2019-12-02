#ifndef MY_JSON_H
#define MY_JSON_H

#include <iostream>
#include <jsoncpp/json/json.h>

class my_json
{
public:
    my_json();
    void start() {
        Json::Value initial_param_;
        initial_param_ = param();
        int id = initial_param_["value"].asInt();
        std::cout << "id " << id << std::endl;
    }

private:
    Json::Value param() {
        Json::Value root;
        root["name"] = "patrol";
        root["value"] = 1;
        return root;
    }
};

#endif // MY_JSON_H
