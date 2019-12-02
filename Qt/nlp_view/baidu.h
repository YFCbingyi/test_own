#ifndef BAIDU_H
#define BAIDU_H

#include <string>
#include <atomic>
#include "nlpbase.h"

#define INTENT_NUM  5
#define SKILL_NUM 2
#define ROS_NUM_GOVERNMENT  "24927"
#define ROS_NUM_TALKING  "24924"

class Baidu : public NlpBase
{
public:
    Baidu();
    virtual bool init();
    virtual void start_(std::string &qus);
private:
    int get_access_token(std::string &access_token, const std::string &AK, const std::string &SK);
    static size_t callback_token(void *ptr, size_t size, size_t nmemb, void *stream);

    static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream);
    int unit_utterance(std::string &json_result, const std::string json_request_body,
                 const std::string &access_token);

    std::string const get_url();
    std::string const organization_message(std::string &text);
    int json_analyze(std::string &msg);
    int get_error_code(std::string &str);
    int get_baidu_bot_result(std::string &str);
    int get_schema_intent(std::string &str);
    int get_baidu_normal_bot_result(std::string &str);
    int get_schema_slots(std::string &str);
    int get_option_list(std::string &str,bool has_condition);
    bool compare_data(std::string &str,int num);
    int organize_actionlist_data(std::string &str,Json::Value &result);
    int organize_data_other(std::string &str,bool flag,int num);
    int organize_data_satisfy(std::string &str);

    std::string get_func_for_func(std::string &str);
    std::string get_id_for_func(std::string &str);
    std::string get_func_for_str(std::string &str);
    std::string get_txt_for_str(std::string &str);
    std::string get_func_for_func_id(std::string &str);
    std::string get_id_for_func_id(std::string &str);

    bool is_capsulation(std::string &src);
    bool isnum(std::string &s);
    bool actionlist_type_isUseable(std::string &str,std::string &action_list_type);
    void business_diff(std::string &str);

    int fetch_info(std::string &str);
    int fetch_info_other(std::string &str);

    void thd_timeout_func(std::string &qus);

private:
    enum schemaintent {SC_IT_NORMAL=0,SC_IT_NULL,SC_IT_NOTFAQ};
    enum bussfunc {BF_GOVERNMENT = 11, BF_AUTOQA, BF_EXPLEN};
    enum tasklevel {FIRST_LEVEL = 0,SECOND_LEVEL ,FINISHED};
    const std::string m_token_url;
    const std::string m_apikey;
    const std::string m_secretkey;

    const std::string m_url_sh_service;
    const std::string m_url_sh_bot;
    const std::string m_url_scgz;
    const std::string m_url_scbj;
    const std::string m_url_scsu;

    std::string m_url_;
    std::string m_token;
    std::string g_session_id;
};

#endif // BAIDU_H
