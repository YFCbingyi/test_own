#include "mybind.h"
#include <iostream>

mybind* mybind::instance_ = NULL;
mybind::mybind(ShowListenCB cb_)
{
    show_listen = cb_;
}

mybind::~mybind() {

}
void mybind::run() {
    std::cout << " run " << std::endl;
    std::string text = "I LOVE CHINA";
    show_string(text);
    Json::Value root;
    root["Good"] = "good";
    root["nlp"] = "nlp";
    show_json(root);
    Json::Value res;
    show_listen(text,res);
    std::cout << " res  "<<res.toStyledString() << std::endl;
    time_out_();
}


