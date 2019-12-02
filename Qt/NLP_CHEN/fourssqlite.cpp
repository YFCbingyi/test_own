#include "fourssqlite.h"
#include <exception>


fourssqlite::fourssqlite()
{
    fours_init();
//    std::vector<std::string> question;
//    std::string scene = "车型列表页";
//    get_text_from_inquiry(scene,question);
//    for(std::vector<std::string>::iterator it = question.begin();it != question.end();it++)
//            std::cout << *it << std::endl;


#if 1
    std::string cond1 = "user_chexing";
    std::string cond2 = "轿车";
    std::string condition;

    get_normalize_form_Dictionary(cond1,cond2,condition);
    std::cout << "条件 "<<condition << std::endl;
    Json::Value result;
    std::cout << "result : "<< result.toStyledString() << std::endl;
    get_jsresult_from_CarClassify(result,condition);

    if(result.empty())
        std::cout << "json 为空";
    std::cout << "result : "<< result.toStyledString() << std::endl;
#else
    show_CarDetail(result);
    Json::Value result_detail;
    get_jsresult_from_CarDetail(result_detail,1);
    std::cout << "result_detail : "<< result_detail.toStyledString() << std::endl;

    Json::Value comp;
    get_jsresult_from_CompanyProfile(comp);
    std::cout << "company : "<<comp.toStyledString()<<std::endl;

    Json::Value service;
    get_jsresult_from_FinanceService(service);
    std::cout << "service : "<< service.toStyledString() <<std::endl;
#endif
}

fourssqlite::~fourssqlite()
{

}

void fourssqlite::fours_init()
{
    m_fs_path = "/home/cby/project/sqlite/auto4s.db";
}

bool fourssqlite::get_json(Json::Value &result)
{
    result["name"] = "chenbingyi";
    result["age"] = 18;
    Json::Value content;
    content["page"] = "home";
    result["res"] = content;
    return true;
}

bool fourssqlite::get_text_from_inquiry(const std::string &scene,std::vector<std::string> &question)
{
    try
    {
        sqlite3pp::database db(m_fs_path.c_str());

        std::string sqlstr = "SELECT text FROM inquiry WHERE scene = \"" + scene+"\" order by prior asc";
        std::cout << sqlstr << std::endl;
        sqlite3pp::query qry(db, sqlstr.c_str());
        for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
            const char* text;
            question.push_back(((text = (*i).get<char const*>(0)) != nullptr ? std::string(text):""));
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "exception :" << e.what() << std::endl;
        return false;
    }
    return true;
}

bool fourssqlite::get_normalize_form_Dictionary(const std::string &name,const std::string &value,std::string &condition)
{
    try
    {
        sqlite3pp::database db(m_fs_path.c_str());

        std::string sqlstr = "SELECT normalize FROM Dictionary WHERE name = \"" + name + "\" and value = \"" + value+"\"";
        std::cout << sqlstr << std::endl;
        sqlite3pp::query qry(db, sqlstr.c_str());
        for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
            const char* text;
            condition = ((text = (*i).get<char const*>(0)) != nullptr ? std::string(text):"");
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "exception :" << e.what() << std::endl;
        return false;
    }
    return true;
}

bool fourssqlite::get_jsresult_from_CarClassify(Json::Value &result,std::string condition)
{
    Json::Value root;
    try
    {
        sqlite3pp::database db(m_fs_path.c_str());

        std::string sqlstr;
        if(condition.empty())
            sqlstr= "select ID,routeID,presentationID,name,img,chexing,pailiangMin,pailiangMax,jiaweiMin,jiaweiMax,zuoweiMin,zuoweiMax,hot,active,lastModified from CarClassify order by hot desc,lastModified  desc";
        else
            sqlstr= "select ID,routeID,presentationID,name,img,chexing,pailiangMin,pailiangMax,jiaweiMin,jiaweiMax,zuoweiMin,zuoweiMax,hot,active,lastModified from CarClassify WHERE "+ condition + " order by hot desc,lastModified  desc";;
        std::cout << sqlstr << std::endl;
        sqlite3pp::query qry(db, sqlstr.c_str());
        for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
            const char* text;
            int m = 0;
            root["ID"] = (*i).get<int>(m++);
            root["routeID"] = (*i).get<int>(m++);
            root["presentationID"] = (*i).get<int>(m++);
            root["name"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["img"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["chexing"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["pailiangMin"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["pailiangMax"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["jiaweiMin"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["jiaweiMax"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["zuoweiMin"] = (*i).get<int>(m++);
            root["zuoweiMax"] = (*i).get<int>(m++);
            root["hot"] = (*i).get<int>(m++);
            root["active"] = (*i).get<int>(m++);
            root["jiawei"] = root["jiaweiMin"].asString()+"-"+root["jiaweiMax"].asString()+"万";
            result["consents"].append(root);
        }
        sqlstr = "select ID,routeID,presentationID,name,img,chexing,pailiangMin,pailiangMax,jiaweiMin,jiaweiMax,zuoweiMin,zuoweiMax,hot,active,lastModified from CarClassify WHERE ID NOT IN (select ID from CarClassify where "+condition +") order by hot desc,lastModified  desc";
        std::cout << sqlstr << std::endl;
        sqlite3pp::query qry_(db, sqlstr.c_str());
        for (sqlite3pp::query::iterator i = qry_.begin(); i != qry_.end(); ++i) {
            const char* text;
            int m = 0;
            root["ID"] = (*i).get<int>(m++);
            root["routeID"] = (*i).get<int>(m++);
            root["presentationID"] = (*i).get<int>(m++);
            root["name"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["img"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["chexing"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["pailiangMin"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["pailiangMax"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["jiaweiMin"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["jiaweiMax"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["jiawei"] = root["jiaweiMin"].asString()+"-"+root["jiaweiMax"].asString()+"万";
            root["zuoweiMin"] = (*i).get<int>(m++);
            root["zuoweiMax"] = (*i).get<int>(m++);
            root["hot"] = (*i).get<int>(m++);
            root["active"] = (*i).get<int>(m++);
            result["consents"].append(root);
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "exception :" << e.what() << std::endl;
        return false;
    }
    return true;
}

bool fourssqlite::get_jsresult_from_CarDetail(Json::Value &result, int carno)
{
    Json::Value root;
    try
    {
        sqlite3pp::database db(m_fs_path.c_str());

        std::string sqlstr = "select ID,presentationID,name,img,chexing,pailiangMin,pailiangMax,jiaweiMin,jiaweiMax,zuoweiMin,zuoweiMax,hot,active,lastModified from CarClassify WHERE id = "+ std::to_string(carno);
        std::cout << sqlstr << std::endl;
        sqlite3pp::query qry(db, sqlstr.c_str());
        for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
            const char* text;
            int m = 0;
            root["ID"] = (*i).get<int>(m++);
            root["presentationID"] = (*i).get<int>(m++);
            root["name"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["img"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["chexing"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["pailiangMin"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["pailiangMax"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["jiaweiMin"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["jiaweiMax"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["zuoweiMin"] = (*i).get<int>(m++);
            root["zuoweiMax"] = (*i).get<int>(m++);
            root["hot"] = (*i).get<int>(m++);
            root["active"] = (*i).get<int>(m++);

        }
        sqlstr = "select ID,name,officialPrice,discount,price,active,lastModified from CarDetail WHERE classifyID = "+ std::to_string(carno);
        std::cout << sqlstr << std::endl;
        sqlite3pp::query qry_(db, sqlstr.c_str());
        for (sqlite3pp::query::iterator i = qry_.begin(); i != qry_.end(); ++i) {
            Json::Value detail;
            const char* text;
            int m = 0;
            detail["ID"] = (*i).get<int>(m++);
            detail["name"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            detail["officialPrice"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            detail["discount"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            detail["price"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            detail["active"] = (*i).get<int>(m++);
            root["subcontents"].append(detail);
        }
        result["res"]["contents"].append(root);
    }
    catch(std::exception &e)
    {
        std::cerr << "exception :" << e.what() << std::endl;
        return false;
    }
    return true;
}

bool fourssqlite::get_jsresult_from_CompanyProfile(Json::Value &result)
{
    Json::Value root;
    try
    {
        sqlite3pp::database db(m_fs_path.c_str());

        std::string sqlstr = "select id,img,active,lastModified from CompanyProfile";
        std::cout << sqlstr << std::endl;
        sqlite3pp::query qry(db, sqlstr.c_str());
        for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
            const char* text;
            int m = 0;
            root["id"] = (*i).get<int>(m++);
            root["img"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["active"] = (*i).get<int>(m++);
            result["res"]["contents"].append(root);
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "exception :" << e.what() << std::endl;
        return false;
    }
    return true;
}


bool fourssqlite::get_jsresult_from_FinanceService(Json::Value &result)
{
    Json::Value root;
    try
    {
        sqlite3pp::database db(m_fs_path.c_str());

        std::string sqlstr = "select id,downPayment,interest,img,active,lastModified from FinanceService";
        std::cout << sqlstr << std::endl;
        sqlite3pp::query qry(db, sqlstr.c_str());
        for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
            const char* text;
            int m = 0;
            root["id"] = (*i).get<int>(m++);
            root["downPayment"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["interest"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["img"] = ((text = (*i).get<char const*>(m++)) != nullptr ? std::string(text):"");
            root["active"] = (*i).get<int>(m++);
            result["res"]["contents"].append(root);
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "exception :" << e.what() << std::endl;
        return false;
    }
    return true;
}

bool fourssqlite::show_CarDetail(Json::Value& contents)
{
    Json::Value res = contents;
    res["page"] = "carDetail";
    std::cout << res.toStyledString() << std::endl;
    Json::Value root;
    root["cmd"] = "change_page";
    root["res"] = res;
    std::cout << root.toStyledString() << std::endl;
}


