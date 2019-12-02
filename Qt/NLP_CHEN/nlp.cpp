#include "nlp.h"
#include <QDebug>
#include "mainwindow.h"

#include <algorithm>

#include <cstdio>

#include <cstring>

#include <cstdlib>

#include <arpa/inet.h>

#include <fstream>

#include <unistd.h>

#include <fcntl.h>
using namespace std;
extern std::string msg_end_result;
std::string s_get_utterance_result;

NLP::NLP(QObject *parent) : QObject(nullptr)
{
    get_mac_address_by_system(userid);
    m_parent = parent;
    qDebug() << "lala ";
    msg_end_result = "";
}
NLP::~NLP()
{

    qDebug() << "lala ";
}

int NLP::tu_unit_utterance(const std::string json_request_body)
{
    std::string url = "http://openapi.tuling123.com/openapi/api/v2";
    CURL *curl = NULL;
    CURLcode result_code;
    int is_success = 0;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        qDebug()<< "url "<<url.data();
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_request_body.data());
        qDebug()<< "json_request_body.data()" << json_request_body.data();
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->tu_callback);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(result_code));
            //qDebug()<< "error code "<<result_code;
            is_success = 1;
            return is_success;
        }
        curl_easy_cleanup(curl);
        is_success = 0;
        tu_rcv_data(s_get_utterance_result);
    } else {
        fprintf(stderr, "curl_easy_init() failed.");
        is_success = 1;
    }
    return is_success;
}

int NLP::tu_send_data(std::string &str)
{
    tu_unit_utterance(str);

    return 0;
}
int NLP::tu_organize_data(std::string &str,std::string &scr)
{
    //qDebug()<< "ready organize data["<< str << "]";

    Json::Value value;
    Json::Value perception;
    Json::Value inputText;
    Json::Value userinfo;
    inputText["text"] = str;
    perception["inputText"] = inputText;
    value["reqType"] = 0;
    value["perception"] = perception;

    userinfo["userId"] = userid;
    userinfo["apiKey"] = apikey;
    value["userInfo"] = userinfo;
    scr = value.toStyledString();
    qDebug()<< "finished organize data["<< endl <<scr.data() << "]";

    return 0;
}

int NLP::tu_rcv_data(std::string &str)
{
    //qDebug()<< "tu rcv data = " <<str;
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    if(DevJson["results"].size() > 0)
    {
        tu_analysis(str);
    }
    else
    {
        tu_check_error_code(str);
    }

    return 0;
}

int NLP::tu_start(std::string &text)
{
    //recieve request
    std::string request;

    //qDebug()<< "recieve request is :" << text << endl;
    //one
    if(tu_organize_data(text,request))
    {
        //qDebug()<< "organize data occue error";
        return 1;
    }
    //qDebug()<< "request : " << request;
    //two
    if(tu_send_data(request))
    {
        //qDebug()<< "failed to send data";
        return 1;
    }

    return 0;
}

int NLP::tu_check_error_code(std::string &str)
{
    switch(tu_get_error_code(str))
    {
            case 5000:
                //qDebug()<< "无解析结果" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 6000:
                //qDebug()<< "暂不支持该功能" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4000:
                //qDebug()<< "请求参数格式错误" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4001:
                //qDebug()<< "加密方式错误" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4002:
                //qDebug()<< "无功能权限" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4003:
                //qDebug()<< "该apikey没有可用请求次数" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4005:
                //qDebug()<< "无功能权限" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4007:
                //qDebug()<< "apikey不合法" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4100:
                //qDebug()<< "userid 获取失败" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4200:
                //qDebug()<< "上传格式错误" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4300:
                //qDebug()<< "批量操作超过限制" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4400:
                //qDebug()<< "没有上传合法userid" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4500:
                //qDebug()<< "userid申请个数超过限制" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4600:
                //qDebug()<< "输入内容为空" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 4602:
                //qDebug()<< "输入文本内容超长(上限150)" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 7002:
                //qDebug()<< "上传信息失败" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            case 8008:
                //qDebug()<< "服务器错误" ;
                tu_error_handle(TU_CODE_ERROR);
                break;
            default:
                //qDebug()<< "未知的错误 ";
                tu_error_handle(TU_CODE_ERROR);
                break;
    }
    return 0;
}

int NLP::tu_get_error_code(std::string &str)
{
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    int error_code = DevJson["intent"]["code"].asInt();
    return error_code;
}

void NLP::tu_analysis(std::string str)
{
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    std::string text;
    for(int i=0;i<(int)DevJson["results"].size();i++)
    {
        if(!DevJson["results"][i]["resultType"].compare("text"))
        {
            text = DevJson["results"][i]["values"]["text"].asString();
        }
    }
    //qDebug()<< "小睿 :" <<text ;
    Json::Value value;
    value["id"].resize(0);
    value["func"] = "";
    value["txt"] = text.c_str();
    value["errorcode"] = 0;
    msg_end_result = value.toStyledString();
    QString msg = QString::fromStdString(msg_end_result);
    ((MainWindow*)m_parent)->show_text(msg);
//    emit send_result_(msg);
    return ;
}

int NLP::tu_error_handle(int error_num)
{
    Json::Value result;
    result["id"].resize(0);
    result["func"] = "";
    switch(error_num)
    {
        case TU_CODE_ERROR:
            result["errorcode"] = TU_CODE_ERROR;
            result["txt"] = "我还在学习中，暂时不能回答你的问题";
            break;
        default:
            break;
    }
    QString msg = QString::fromStdString(msg_end_result);
    ((MainWindow*)m_parent)->show_text(msg);
//    emit send_result_(msg);
    return 0;
}
size_t NLP::tu_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{

    std::string msg;
    s_get_utterance_result = std::string((char *) ptr, size * nmemb);
    //qDebug() << stream;
    qDebug()<< "result "<< s_get_utterance_result.data();

    return size * nmemb;
}


bool NLP::get_mac_address_by_system(std::string & mac_address)
{
    mac_address.c_str();

    const char * lshw_result = ".lshw_result.txt";
    char command[512] = { 0 };
    snprintf(command, sizeof(command), "lshw -c network | grep serial | head -n 1 > %s", lshw_result);

    if (0 == system(command))
    {
        parse_mac_address(lshw_result, "serial:", mac_address);
    }

    unlink(lshw_result);

    return(!mac_address.empty());
}
void NLP::parse_mac_address(const char * file_name, const char * match_words, std::string & mac_address)
{
    mac_address.c_str();

    std::ifstream ifs(file_name, std::ios::binary);
    if (!ifs.is_open())
    {
        return;
    }

    char line[4096] = { 0 };
    while (!ifs.eof())
    {
        ifs.getline(line, sizeof(line));
        if (!ifs.good())
        {
            break;
        }

        const char * mac = strstr(line, match_words);
        if (NULL == mac)
        {
            continue;
        }
        mac += strlen(match_words);

        while ('\0' != mac[0])
        {
            if (' ' != mac[0] && ':' != mac[0])
            {
                mac_address.push_back(mac[0]);
            }
            ++mac;
        }

        if (!mac_address.empty())
        {
            break;
        }
    }

    ifs.close();
}
