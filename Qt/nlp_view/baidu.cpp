#include <curl/curl.h>
#include <iostream>
#include "debug_log.h"
#include "baidu.h"
#include <ctime>
#include <sstream>
#include <chrono>
static std::string complete_rcv_data = "";
Baidu::Baidu() : m_token_url("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials"),m_apikey("KGLQLzDVQjcQCWEyEc612TcN"),m_secretkey("Mx7p13zYPpO4QyHEOrdPN6jb9o28fcLd"),
    m_url_sh_service("https://aip.baidubce.com/rpc/2.0/unit/service/chat"),m_url_sh_bot("https://aip.baidubce.com/rpc/2.0/unit/bot/chat"),m_url_scgz("https://unit.gz.baidubce.com/rpc/2.0/unit/bot/chat"),m_url_scbj("https://unit.bj.baidubce.com/rpc/2.0/unit/bot/chat"),m_url_scsu("https://unit.su.baidubce.com/rpc/2.0/unit/bot/chat"),m_url_(""),m_token(""),g_session_id("")
{
}

size_t Baidu::callback_token(void *ptr, size_t size, size_t nmemb, void *stream) {
    // 获取到的body存放在ptr中，先将其转换为string格式
    std::string s((char *) ptr, size * nmemb);
    Json::Reader reader;
    Json::Value root;
    reader.parse(s,root);
    std::string* access_token_result = static_cast<std::string*>(stream);
    *access_token_result = root["access_token"].asString();
    return size * nmemb;
}

int Baidu::get_access_token(std::string &access_token, const std::string &AK, const std::string &SK) {
    CURL *curl;
    CURLcode result_code;
    int error_code = 0;
    curl = curl_easy_init();
    if (curl) {
        std::string url = m_token_url + "&client_id=" + AK + "&client_secret=" + SK;
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        std::string access_token_result;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &access_token_result);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->callback_token);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result_code));
            return 1;
        }
        access_token = access_token_result;
        curl_easy_cleanup(curl);
        error_code = 0;
    } else {
        fprintf(stderr, "curl_easy_init() failed.");
        error_code = 1;
    }
    return error_code;
}

size_t Baidu::callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    // 获取到的body存放在ptr中，先将其转换为string格式
    std::string s_get_utterance_result = std::string((char *) ptr, size * nmemb);
    complete_rcv_data += s_get_utterance_result;
    return size * nmemb;
}

int Baidu::unit_utterance(std::string &json_result, const std::string json_request_body,
             const std::string &access_token) {
    if(get_random_number(0,2) == 1) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    this->error_handle(CODE_EMPTY);
    return 0;
    complete_rcv_data.clear();
    std::string url = m_url_ + "?access_token=" + access_token;
    CURL *curl = NULL;
    CURLcode result_code;
    int is_success = 0;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        LOG(INFO) << "NLP: url "<<url.data();
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_request_body.data());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->callback);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result_code));
                    LOG(ERROR) << "NLP: error code "<<result_code;
            return result_code;
        }
        json_result = complete_rcv_data;
        complete_rcv_data.clear();
        curl_easy_cleanup(curl);
        is_success = 0;
    } else {
        fprintf(stderr, "curl_easy_init() failed.");
        is_success = 1;
    }
    return is_success;
}

bool Baidu::init() {
    this->initial();
    m_url_ = get_url();
    int errno;
    while(m_token.empty()) {
        if((errno = get_access_token(m_token,m_apikey,m_secretkey))) {
            LOG(INFO) << "Baidu::init : "<<errno;
            if(errno == 1) ///网络断开的时候，没有网的时候
                return false;
        } else {
            LOG(INFO) << "Baidu::init : m_token is "<<m_token;
            break;
        }
    }
    return true;
}

std::string const Baidu::get_url() {
    if(!m_version.compare("product")) {
        if(m_region.compare("bj") == 0) {
            return m_url_scbj;
        } else if(m_region.compare("gz") == 0) {
            return m_url_scgz;
        } else if(m_region.compare("su") == 0) {
            return m_url_scsu;
        }
    } else if(!m_version.compare("sandbox_bot")) {
        return m_url_sh_bot;
    } else {
        return m_url_sh_service;
    }
}

void Baidu::start_(std::string &qus) {
    std::chrono::time_point<std::chrono::high_resolution_clock> m_durtime = std::chrono::high_resolution_clock::now();
    m_taskfinished = false;
    std::thread t(&Baidu::thd_timeout_func,this,std::ref(qus));
    this->thread_id_ = t.get_id();
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_durtime).count() > m_timeout) {
            t.detach();
            this->error_handle(CODE_NONETWORK);
            return;
            ///
        }
        if(m_taskfinished)
            break;
    }
    if(t.joinable())
        t.join();
}

void Baidu::thd_timeout_func(std::string &qus) {
    std::string que_json = Baidu::organization_message(qus);
    LOG(INFO) << "Baidu::start_ : question_json  "<<que_json;
    std::string res_json;
    if(Baidu::unit_utterance(res_json,que_json,m_token)) {
        //失败
    }
    json_analyze(res_json);
    if(thread_id_ == std::this_thread::get_id())
        m_taskfinished = true;
    else
        LOG(ERROR) << " time out";
}

std::string const Baidu::organization_message(std::string &text) {
    std::string out;
    if((!m_version.compare("product")) || (!m_version.compare("sandbox_bot"))) {
        Json::Value request;
        request["query"] = text;
        request["user_id"] = this->m_userid;
        request["updates"] = "";
        Json::Value qurey_info;
        qurey_info["type"] = "TEXT";
        qurey_info["source"] = "KEYBOARD";
        qurey_info["asr_candidates"].resize(0);
        request["query_info"] = qurey_info;
        request["client_session"] = "{\"client_results\":\"\", \"candidate_options\":[]}";
        request["bernard_level"] = 1;

        Json::Value value;
        value["version"] = "2.0";
        value["log_id"] = "7758521";
        value["bot_session"] = g_session_id;
        value["request"] = request;
        value["bot_id"] = this->m_botid;
        out = value.toStyledString();
    } else if(!m_version.compare("sandbox_service")) {
        Json::Value request;
        request["query"] = text;
        request["user_id"] = this->m_userid;
        Json::Value context;
        context["SYS_REMEMBERED_SKILLS"].resize(0);
        Json::Value dialog_state;
        dialog_state["contexts"] = context;
        Json::Value value;
        value["version"] = "2.0";
        value["service_id"] = "S11197";
        value["log_id"] = "UNITTEST_10000";
        value["session_id"] = "";
        value["request"] = request;
        value["dialog_state"] = dialog_state;
        out = value.toStyledString();
    } else {
        LOG(ERROR)<<"Baidu::organization_message : version config failed";
    }
    return out;
}

int Baidu::json_analyze(std::string &msg) {
    //error_code
    if(get_error_code(msg) >= 292001 && get_error_code(msg) <= 292015)
        error_handle(CODE_NOT_USE);
    else if(get_error_code(msg) >= 299001 && get_error_code(msg) <= 299999)
        error_handle(CODE_RESEND);
    else {
        switch(get_error_code(msg)) {
        case 0:
            if((!m_version.compare("product")) || (!m_version.compare("sandbox_bot")))
                get_baidu_bot_result(msg);
            else
                business_diff(msg);
            break;
        case 1:
        case 2:
            error_handle(CODE_RESEND);
            break;
        case 3:
            error_handle(CODE_NOT_USE);
            break;
        case 4:
            error_handle(CODE_NOT_USE);
            break;
        case 6:
            error_handle(CODE_NOT_USE);
            break;
        case 17:
        case 18:
        case 19:
            error_handle(CODE_NOT_USE);
            break;
        case 100:
            error_handle(CODE_GET_TOKEN);
            break;
        case 110:
        case 111:
            error_handle(CODE_GET_TOKEN);
            break;
        case 282000:
        case 282001:
            error_handle(CODE_RESEND);
            break;
        case 282004:
            error_handle(CODE_NOT_USE);
            break;
        case 282008:
            error_handle(CODE_NOT_USE);
            break;
        case 282906:
            error_handle(CODE_RESEND);
        default:
            LOG(ERROR) << "NLP: unknow error occur";
            break;
        }
    }
    return 0;
}

int Baidu::get_error_code(std::string &str) {
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    int error_code;
    if(!DevJson["error_code"].isInt())
        error_code = DevJson["errno"].asInt();
    else
        error_code = DevJson["error_code"].asInt();
    return error_code;
}

int Baidu::get_baidu_bot_result(std::string &str) {
    std::string action_list_type;
    switch(get_schema_intent(str)) {
    case SC_IT_NORMAL:
        g_session_id.clear();
        if(get_baidu_normal_bot_result(str)) {
            ///todo 出错
        }
        break;
    case SC_IT_NOTFAQ:
        if(actionlist_type_isUseable(str,action_list_type)) {
            if(!action_list_type.compare("clarify")) {
                get_schema_slots(str);
            } else if(!action_list_type.compare("failure")) {
                if(!g_session_id.empty()) {
                    Json::Value result;
                    result["func"]="clarify_error";
                    result["errorcode"] = CODE_ZERO;
                    msg_end_result = result.toStyledString();
                    g_session_id.clear();
                }
            } else if(!action_list_type.compare("guide")) {
                get_option_list(str,false);
                g_session_id.clear();
            } else if(!action_list_type.compare("satisfy")) {
                get_option_list(str,true);
                g_session_id.clear();
            }
        }
        else
            error_handle(ERROR_TYPE);
        break;
    case SC_IT_NULL:
        g_session_id.clear();
        error_handle(ERROR_TYPE);
        break;
    }
    return 0;
}

int Baidu::get_schema_intent(std::string &str) {
    Json::Reader Reader;
    Json::Value DevJson;
    try {
        Reader.parse(str,DevJson);
        std::string schema_intent = DevJson["result"]["response"]["schema"]["intent"].asString();
        if(schema_intent.empty())
            return SC_IT_NULL;
        if((schema_intent.length() > 4) && (!schema_intent.substr(0,4).compare("FAQ_")))
            return SC_IT_NORMAL;
        else
            return SC_IT_NOTFAQ;
    } catch(std::exception &e) {
        LOG(ERROR) << "Baidu::get_schema_intent : exception : "<<e.what();
    }
}

int Baidu::get_schema_slots(std::string &str) {
    Json::Value result;
    Json::Reader Reader;
    Json::Value DevJson;
    try {
        Reader.parse(str,DevJson);
        g_session_id = DevJson["result"]["bot_session"].asString();

        int schema_slots_size = DevJson["result"]["response"]["schema"]["slots"].size();
        for(int i = 0;i < schema_slots_size; i++) {
            std::string condition = DevJson["result"]["response"]["schema"]["slots"][i]["name"].asString()+" : "+DevJson["result"]["response"]["schema"]["slots"][i]["normalized_word"].asString();
            result["condition"].append(condition.c_str());
        }
        int action_list_sum = DevJson["result"]["response"]["action_list"].size();
        for(int i=0;i<action_list_sum;i++) {
            std::string say = DevJson["result"]["response"]["action_list"][i]["say"].asString();
            organize_actionlist_data(say,result);
            msg_end_result = result.toStyledString();
            return 0;
        }
        msg_end_result = result.toStyledString();
    } catch(std::exception &e) {
        LOG(ERROR) << "Baidu::get_schema_slots : exception : "<<e.what();
    }
    return 0;
}

int Baidu::get_option_list(std::string &str,bool has_condition) {
    Json::Value result;
    Json::Reader Reader;
    Json::Value DevJson;
    try {
        Reader.parse(str,DevJson);
        if(has_condition) {
            int schema_slots_size = DevJson["result"]["response"]["schema"]["slots"].size();
            for(int i = 0;i < schema_slots_size; i++) {
                std::string condition = DevJson["result"]["response"]["schema"]["slots"][i]["name"].asString()+" : "+DevJson["result"]["response"]["schema"]["slots"][i]["normalized_word"].asString();
                result["condition"].append(condition.c_str());
            }
        }
        int action_list_sum = DevJson["result"]["response"]["action_list"].size();
        for(int i=0;i<action_list_sum;i++) {
            int option_list_num = DevJson["result"]["response"]["action_list"][i]["refine_detail"]["option_list"].size();
            for(int j=0; j<option_list_num; j++) {
                result["optionlist"].append(DevJson["result"]["response"]["action_list"][i]["refine_detail"]["option_list"][j]["option"].asString().c_str());
            }
            std::string say = DevJson["result"]["response"]["action_list"][i]["say"].asString();
            organize_actionlist_data(say,result);
            msg_end_result = result.toStyledString();
            return 0;
        }
    } catch(std::exception &e) {
        LOG(ERROR) << "Baidu::get_option_list : exception : "<<e.what();
    }
}

bool Baidu::actionlist_type_isUseable(std::string &str,std::string &action_list_type) {
    Json::Reader Reader;
    Json::Value DevJson;
    try {
        Reader.parse(str,DevJson);
        int action_list_sum = DevJson["result"]["response"]["action_list"].size();
        for(int i=0;i<action_list_sum;i++) {
            action_list_type = DevJson["result"]["response"]["action_list"][i]["type"].asString();
            if((!action_list_type.compare("guide")) || (!action_list_type.compare("satisfy")))
                return true;
            else if(!action_list_type.compare("clarify"))
                return true;
            else if(!action_list_type.compare("failure"))
                return true;
            return false;
        }
    } catch(std::exception &e) {
        LOG(ERROR) << "Baidu::actionlist_type_isUseable : exception : "<<e.what();
    }
}

int Baidu::get_baidu_normal_bot_result(std::string &str) {
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    try {
        if(DevJson["result"]["response"]["action_list"][0]["type"].asString().compare("guide") == 0 ||
                DevJson["result"]["response"]["action_list"][0]["type"].asString().compare("clarify") == 0) {
            int candidate_num = DevJson["result"]["response"]["qu_res"]["candidates"].size();

            std::string msg_info = DevJson["result"]["response"].toStyledString();
            LOG(INFO) << "NLP: guide-clarify msg_info "<< msg_info ;
            if(candidate_num > 0 && candidate_num < INTENT_NUM) {
                if(compare_data(msg_info,candidate_num))
                    organize_data_other(msg_info,false,candidate_num);
                else
                    organize_data_other(msg_info,true,candidate_num);
            } else if(candidate_num >= INTENT_NUM) {
                if(compare_data(msg_info,INTENT_NUM))
                    organize_data_other(msg_info,false,INTENT_NUM);
                else
                    organize_data_other(msg_info,true,INTENT_NUM);
            } else {
                LOG(ERROR) << "Baidu::get_baidu_normal_bot_result : intent num error ";
                return -1;
            }
        } else if(DevJson["result"]["response"]["action_list"][0]["type"].asString().compare("satisfy") == 0) {
            std::string msg_info = DevJson["result"]["response"]["action_list"][0]["say"].asString();
            LOG(INFO) << "Baidu::get_baidu_normal_bot_result : satisfy msg_info "<< msg_info ;
            if(organize_data_satisfy(msg_info)) {
                LOG(ERROR) << "Baidu::get_baidu_normal_bot_result : organize data satisfy failed ";
            }
        }
    } catch (std::exception &e) {
        LOG(ERROR) << "Baidu::get_baidu_normal_bot_result : exception : "<<e.what();
    }

    return 0;
}

int Baidu::organize_data_other(std::string &str,bool flag,int num) {
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    std::string msg;
    Json::Value result;
getonce:
    if(flag) {
        //==
        msg = DevJson["qu_res"]["candidates"][0]["slots"][0]["normalized_word"].asString();
        if(!is_capsulation(msg)) {
            std::string txt = msg;
            result["txt"] = txt.c_str();
            result["id"].resize(0);
            result["errorcode"] = CODE_ZERO;
            msg_end_result = result.toStyledString();
            return 0;
        }
        std::string funcid = get_func_for_str(msg);
        std::string func = get_func_for_func(funcid);
        std::string id = get_id_for_func(funcid);
        std::string txt = get_txt_for_str(msg);
        result["func"] = func.c_str();
        result["id"].append(id.c_str());
        result["txt"] = txt.c_str();
    } else {
        result["id"].resize(0);
        bool id_is_str_ = false;
        bool id_is_num_ = false;
        bool all_has_id_ = true;
        std::vector<std::string> normalized_word_group;
        for(int i=0;i<num;i++) {
            msg = DevJson["qu_res"]["candidates"][i]["slots"][0]["normalized_word"].asString();
            if(!is_capsulation(msg)) {
                all_has_id_ = false;
                normalized_word_group.push_back(msg);
                continue;
            }
            std::string funcid = get_func_for_str(msg);
            std::string func = get_func_for_func(funcid);
            std::string id = get_id_for_func(funcid);
            std::string func_id = func+"###"+id;
            normalized_word_group.push_back(func_id);

            if(isnum(id))
                id_is_num_ = true;
            else
                id_is_str_ = true;
        }
        if(id_is_num_ && id_is_str_) {
            LOG(INFO) << "Baidu::organize_data_other : id is str and num" ;
            error_handle(ERROR_TYPE);
            return 0;
        } else if(id_is_num_ && !id_is_str_ && all_has_id_) {
            LOG(INFO) << "Baidu::organize_data_other : id is only num";
            for(auto m = normalized_word_group.begin(); m != normalized_word_group.end();m++) {
                if(!is_capsulation(*m))
                    continue;
                std::string id = get_id_for_func_id(*m);
                bool flag = true;
                for(int i = 0; i < result["id"].size(); i++) {
                    if(!result["id"][i].asString().compare(id.c_str())) {
                        flag = false;
                        break;
                    }
                }
                if(flag)
                    result["id"].append(id.c_str());
            }
        } else if((!id_is_num_ && id_is_str_) || !all_has_id_) {
            LOG(INFO) << "Baidu::organize_data_other : id is only str";
            flag = true;
            goto getonce;
        }
    }
    result["errorcode"] = CODE_ZERO;
    msg_end_result = result.toStyledString();
    return 0;
}

int Baidu::organize_data_satisfy(std::string &str) {
    Json::Value result;
    if(!is_capsulation(str)) {
        std::string txt = str;
        result["txt"] = txt.c_str();
        result["id"].resize(0);
        result["errorcode"] = CODE_ZERO;
        msg_end_result = result.toStyledString();
        return 0;
    }
    std::string funcid = get_func_for_str(str);
    std::string func = get_func_for_func(funcid);
    std::string id = get_id_for_func(funcid);
    std::string txt = get_txt_for_str(str);
    result["func"] = func.c_str();
    result["id"].append(id.c_str());
    result["txt"] = txt.c_str();
    result["errorcode"] = CODE_ZERO;

    msg_end_result = result.toStyledString();
    return 0;
}

bool Baidu::compare_data(std::string &str,int num) {
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    std::string intent = DevJson["qu_res"]["candidates"][0]["intent"].asString();;
    for(int i=1;i<num;i++) {
        if(DevJson["qu_res"]["candidates"][i]["intent"].asString().compare(intent.c_str()))
            return true;
    }
    return false;
}

int Baidu::organize_actionlist_data(std::string &str,Json::Value &result) {
    if(!is_capsulation(str)) {
        std::string txt = str;
        result["txt"] = txt.c_str();
        result["id"].resize(0);
        result["errorcode"] = CODE_ZERO;
        msg_end_result = result.toStyledString();
        return 0;
    }
    std::string funcid = get_func_for_str(str);
    std::string func = get_func_for_func(funcid);
    std::string id = get_id_for_func(funcid);
    std::string txt = get_txt_for_str(str);
    result["func"] = func.c_str();
    if(!id.empty())
        result["id"].append(id.c_str());
    result["txt"] = txt.c_str();
    result["errorcode"] = CODE_ZERO;
    return 0;
}

bool Baidu::is_capsulation(std::string &src) {
    if(src.find("###") != std::string::npos)
        return true;
    else
        return false;
}

std::string Baidu::get_func_for_func(std::string &str) {
    int start = str.find("(");
    std::string func = str.length() > start ? str.substr(0,start) : "";
//    std::string func = str.substr(0,start);
    return func;
}

std::string Baidu::get_func_for_func_id(std::string &str){
    int start = str.find("###");
    std::string func = str.length() > start ? str.substr(0,start) : "";
//    std::string func = str.substr(0,start);
    return func;
}

std::string Baidu::get_id_for_func_id(std::string &str){
    int end = str.rfind("###");
    std::string id = str.length() > end ? str.substr(end+3) : "";
//    std::string id = str.substr(end+3);
    return id;
}

std::string Baidu::get_id_for_func(std::string &str) {
    int start = str.find("(");
    int end = str.rfind(")");
    std::string id = (str.length() > start && str.length() > end) ? str.substr(start+1,end-start-1) : "";
//    std::string id = str.substr(start+1,end-start-1);
    return id;
}

std::string Baidu::get_func_for_str(std::string &str) {
    int start = str.find("###");
    int end = str.rfind("###");
    std::string func = (str.length() > start && str.length() > end) ? str.substr(start+3,end-start-3) : "";
//    std::string func = str.substr(start+3,end-start-3);
    return func;
}

std::string Baidu::get_txt_for_str(std::string &str) {
    int end = str.rfind("###");
    std::string txt = str.length() > end ? str.substr(end+3) : "";
//    std::string txt = str.substr(end+3);
    return txt;
}

bool Baidu::isnum(std::string &s)
{
    std::stringstream sin(s);
    double t;
    char p;
    if(!(sin >> t))
        /*解释：
           sin>>t表示把sin转换成double的变量（其实对于int和float型的都会接收），如果转换成功，则值为非0，如果转换不成功就返回为0
       */
        return false;
    if(sin >> p)
        /*解释：此部分用于检测错误输入中，数字加字符串的输入形式（例如：34.f），在上面的的部分（sin>>t）已经接收并转换了输入的数字部分，在stringstream中相应也会把那一部分给清除，如果此时传入字符串是数字加字符串的输入形式，则此部分可以识别并接收字符部分，例如上面所说的，接收的是.f这部分，所以条件成立，返回false;如果剩下的部分不是字符，那么则sin>>p就为0,则进行到下一步else里面
         */
        return false;
    else
        return true;
}

void Baidu::business_diff(std::string &str)
{
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    Json::Value value;
    bool is_success = -1;
    LOG(INFO) << "NLP: response_list.size() is "<<DevJson["result"]["response_list"].size();
    for(int i=0;i<DevJson["result"]["response_list"].size();i++) {
        LOG(INFO) << "NLP: origin is :"<< DevJson["result"]["response_list"][i]["origin"].asString();
        if(!DevJson["result"]["response_list"][i]["origin"].asString().compare(ROS_NUM_GOVERNMENT)) {
            value = DevJson["result"]["response_list"][i];
            std::string msg_govern = value.toStyledString();
            if(!fetch_info(msg_govern)) {
                is_success = 0;
                break;
            }
        } else if(!DevJson["result"]["response_list"][i]["origin"].asString().compare(ROS_NUM_TALKING)) {
            LOG(INFO)<<"NLP: 智能问答";
            value = DevJson["result"]["response_list"][i];
            std::string msg_talking = value.toStyledString();
            if(!fetch_info_other(msg_talking)) {
                is_success = 0;
                break;
            }
        }
    }
    if(is_success == -1) {
        error_handle(ERROR_TYPE);
    }
}

int Baidu::fetch_info_other(std::string &str) {
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    std::string msg_info;
    try {
        //action_list 目前只有一个成员
        if(!DevJson["action_list"][0]["type"].asString().compare("satisfy")) {
            //type 命中 satisfy
            msg_info = DevJson["action_list"][0]["say"].asString();
            LOG(INFO) << "Baidu::fetch_info_other : say :" << msg_info;
            organize_data_satisfy(msg_info);
        } else
            return -1;
    } catch (std::exception &e) {
        LOG(ERROR) << "Baidu::fetch_info_other : exception : "<<e.what();
    }
    return 0;
}
int Baidu::fetch_info(std::string &str) {
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    std::string msg_info;
    //action_list 目前只有一个成员
    try {
        if(!DevJson["action_list"][0]["type"].asString().compare("satisfy")) {
            //type 命中 satisfy
            msg_info = DevJson["action_list"][0]["say"].asString();
            organize_data_satisfy(msg_info);
        } else if(!DevJson["action_list"][0]["type"].asString().compare("guide") ||
            !DevJson["action_list"][0]["type"].asString().compare("clarify")) {
            //type 为 guide 或者 clarify
            //分析参数中candidates的intent值
            int candidate_num = DevJson["qu_res"]["candidates"].size();
            if(candidate_num > 0 && candidate_num < INTENT_NUM) {
                if(compare_data(str,candidate_num))
                    organize_data_other(str,false,candidate_num);
                else
                    organize_data_other(str,true,candidate_num);
            } else if(candidate_num >= INTENT_NUM) {
                if(compare_data(str,INTENT_NUM))
                    organize_data_other(str,false,INTENT_NUM);
                else
                    organize_data_other(str,true,INTENT_NUM);
            } else {
                LOG(ERROR) << "Baidu::fetch_info : intent num error ";
                return -1;
            }
        } else
            return -1;
    } catch (std::exception &e) {
        LOG(ERROR) << "Baidu::fetch_info : exception : "<<e.what();
    }
    return 0;
}

