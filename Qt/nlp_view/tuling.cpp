#include "tuling.h"
#include "debug_log.h"
#include <chrono>
#include <curl/curl.h>
static std::string complete_rcv_data = "";
Tuling::Tuling() : apikey("cbdd86e85f974130b5cac506c4efab10") {

}
void Tuling::start_(std::string &qus) {
    std::chrono::time_point<std::chrono::high_resolution_clock> m_durtime = std::chrono::high_resolution_clock::now();
    m_taskfinished = false;
    std::thread t(&Tuling::thd_timeout_func,this,std::ref(qus));
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

void Tuling::thd_timeout_func(std::string &qus) {
    std::string que_json = organization_message(qus);
    LOG(INFO) << "Tuling::thd_timeout_func : question_json  "<<que_json;
    std::string res_json;
    if(unit_utterance(res_json,que_json)) {
        //失败
    }
    tu_rcv_data(res_json);
    if(thread_id_ == std::this_thread::get_id())
        m_taskfinished = true;
    else
        LOG(ERROR) << " time out";
}

size_t Tuling::tu_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string s_get_utterance_result;
    s_get_utterance_result = std::string((char *) ptr, size * nmemb);

    LOG(INFO) << "NLP: result "<<s_get_utterance_result;
    complete_rcv_data += s_get_utterance_result;
    return size * nmemb;
}
int Tuling::unit_utterance(std::string &json_result, const std::string json_request_body)
{
    std::string url = "http://openapi.tuling123.com/openapi/api/v2";
    CURL *curl = NULL;
    CURLcode result_code;
    int is_success = 0;
    complete_rcv_data.clear();
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        LOG(INFO) << "NLP: tuling url "<<url.data();
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_request_body.data());
        LOG(INFO) << "NLP: json_request_body.data()" << json_request_body.data();
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, tu_callback);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result_code));
                    LOG(ERROR) << "NLP: error code "<<result_code;
            is_success = 1;
            return is_success;
        }
        curl_easy_cleanup(curl);
        is_success = 0;
        json_result = complete_rcv_data;
    } else {
        fprintf(stderr, "curl_easy_init() failed.");
        is_success = 1;
    }
    return is_success;
}

int Tuling::tu_rcv_data(std::string &str)
{
    LOG(INFO) << "NLP: tu rcv data = " <<str ;
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    if(DevJson["results"].size() > 0) {
        tu_analysis(str);
    } else {
        tu_check_error_code(str);
    }
    return 0;
}

std::string const Tuling::organization_message(std::string &text) {
    std::string out;
    Json::Value value;
    Json::Value perception;
    Json::Value inputText;
    Json::Value userinfo;
    inputText["text"] = text;
    perception["inputText"] = inputText;
    value["reqType"] = 0;
    value["perception"] = perception;

    userinfo["userId"] = m_userid;
    userinfo["apiKey"] = apikey;
    value["userInfo"] = userinfo;
    out = value.toStyledString();
    return out;
}

int Tuling::tu_check_error_code(std::string &str)
{
    switch(tu_get_error_code(str))
    {
            case 5000:
                LOG(ERROR) << "NLP: 无解析结果" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 6000:
                LOG(ERROR) << "NLP: 暂不支持该功能" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4000:
                LOG(ERROR) << "NLP: 请求参数格式错误" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4001:
                LOG(ERROR) << "NLP: 加密方式错误" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4002:
                LOG(ERROR) << "NLP: 无功能权限" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4003:
                LOG(ERROR) << "NLP: 该apikey没有可用请求次数" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4005:
                LOG(ERROR) << "NLP: 无功能权限" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4007:
                LOG(ERROR) << "NLP: apikey不合法" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4100:
                LOG(ERROR) << "NLP: userid 获取失败" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4200:
                LOG(ERROR) << "NLP: 上传格式错误" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4300:
                LOG(ERROR) << "NLP: 批量操作超过限制" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4400:
                LOG(ERROR) << "NLP: 没有上传合法userid" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4500:
                LOG(ERROR) << "NLP: userid申请个数超过限制" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4600:
                LOG(ERROR) << "NLP: 输入内容为空" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 4602:
                LOG(ERROR) << "NLP: 输入文本内容超长(上限150)" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 7002:
                LOG(ERROR) << "NLP: 上传信息失败" ;
                error_handle(TU_CODE_ERROR);
                break;
            case 8008:
                LOG(ERROR) << "NLP: 服务器错误" ;
                error_handle(TU_CODE_ERROR);
                break;
            default:
                LOG(ERROR) << "NLP: 未知的错误 ";
                error_handle(TU_CODE_ERROR);
                break;
    }
}

int Tuling::tu_get_error_code(std::string &str)
{
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    int error_code = DevJson["intent"]["code"].asInt();
    return error_code;
}

void Tuling::tu_analysis(std::string str)
{
    Json::Reader Reader;
    Json::Value DevJson;
    Reader.parse(str,DevJson);
    std::string text;
    for(int i=0;i<DevJson["results"].size();i++)
    {
        if(!DevJson["results"][i]["resultType"].compare("text"))
        {
            text = DevJson["results"][i]["values"]["text"].asString();
        }
    }
    LOG(INFO) << "NLP: " <<text ;
    Json::Value value;
    value["id"].resize(0);
    value["func"] = "";
    value["txt"] = text.c_str();
    value["errorcode"] = 0;
    msg_end_result = value.toStyledString();
    return ;
}

