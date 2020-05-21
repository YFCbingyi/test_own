#ifndef BAIDU_DEPLOY_H
#define BAIDU_DEPLOY_H
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <curl/curl.h>

#include "jsoncpp/json/json.h"
#include <algorithm>

using namespace std;

class BaiduDeploy
{
public:
    //获取token
    int get_access_token(std::string &access_token, const std::string &AK, const std::string &SK);
    static size_t callback_token(void *ptr, size_t size, size_t nmemb, void *stream);

    //获取result
    int unit_utterance(std::string &json_result, const std::string json_request_body,
                       const std::string &access_token);
    static size_t callback_result(void *ptr, size_t size, size_t nmemb, void *stream);

    ///生产环境
    std::string get_utterance_url;
    enum TASK_ID {TASK_ADD=0, TASK_UPDATE, TASK_GET_STATE, TASK_DELATE};
    std::string organiza_msg_product(const int cmdId,int botid,std::string &region,std::string &module,int taskid = 0);
    ///生产环境 -by cby 2019-03-28

    ///结果
    int get_errorcode(std::string &str);
    std::string get_error_msg(std::string &str);
    ///结果 -cby -2019-03-29

    bool set_deploymentId(std::string &str);
    int get_deploymentId(int botid);

    bool inital();

    int m_botid;
    std::string m_region;
    std::string m_model;

private:


};

#endif
