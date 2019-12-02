#ifndef FOURSSQLITE_H
#define FOURSSQLITE_H

#include <string>
#include "sqlite3pp.h"
#include <jsoncpp/json/json.h>
#include <iostream>
class fourssqlite
{
public:
    fourssqlite();
    ~fourssqlite();

private:
    void fours_init();
    bool get_text_from_inquiry(const std::string &scene,std::vector<std::string> &question);
    bool get_normalize_form_Dictionary(const std::string &name,const std::string &value,std::string &condition);
    bool get_jsresult_from_CarDetail(Json::Value &result,int carno);
    bool get_jsresult_from_CarClassify(Json::Value &result,std::string condition="");
    bool get_jsresult_from_CompanyProfile(Json::Value &result);
    bool get_jsresult_from_FinanceService(Json::Value &result);

    bool show_CarDetail(Json::Value& contents);
    bool get_json(Json::Value &result);
    bool show_carinfo(std::vector<int> &car_id,Json::Value &result);

    std::string m_fs_path;
};


#endif // FOURSSQLITE_H
