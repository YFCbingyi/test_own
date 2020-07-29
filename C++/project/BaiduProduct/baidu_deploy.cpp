#include "baidu_deploy.h"
#include "debug_log.h"
#include <exception>

std::string BaiduDeploy::organiza_msg_product(const int cmdId, int botid, std::string &region, std::string &module, int taskid)
{
    Json::Value value;
    switch (cmdId)
    {
    case TASK_ADD:
        value["botId"] = botid;
        value["region"] = region;
        value["modelVersion"] = module;
        get_utterance_url = "https://aip.baidubce.com/rpc/2.0/unit/deployment/add";
        break;
    case TASK_UPDATE:
        value["botId"] = botid;
        value["region"] = region;
        value["modelVersion"] = module;
        get_utterance_url = "https://aip.baidubce.com/rpc/2.0/unit/deployment/updateModelVersion";
        break;
    case TASK_GET_STATE:
        value["botId"] = botid;
        value["deploymentId"] = taskid;
        get_utterance_url = "https://aip.baidubce.com/rpc/2.0/unit/deployment/getStatus";
        break;
    default:
        break;
    }
    std::string out = value.toStyledString();
    return out;
}

/**

 * curl发送http请求调用的回调函数，回调函数中对返回的json格式的body进行了解析，解析结果储存在result中

 * @param 参数定义见libcurl库文档

 * @return 返回值定义见libcurl库文档

 */

size_t BaiduDeploy::callback_token(void *ptr, size_t size, size_t nmemb, void *stream)
{

    // 获取到的body存放在ptr中，先将其转换为string格式

    std::string s((char *)ptr, size * nmemb);

    // 开始获取json中的access token项目

    Json::Reader reader;

    Json::Value root;

    // 使用boost库解析json

    reader.parse(s, root);

    std::string *access_token_result = static_cast<std::string *>(stream);

    *access_token_result = root["access_token"].asString();

    return size * nmemb;
}

/**

 * 用以获取access_token的函数，使用时需要先在百度云控制台申请相应功能的应用，获得对应的API Key和Secret Key

 * @param access_token 获取得到的access token，调用函数时需传入该参数

 * @param AK 应用的API key

 * @param SK 应用的Secret key

 * @return 返回0代表获取access token成功，其他返回值代表获取失败

 */

int BaiduDeploy::get_access_token(std::string &access_token, const std::string &AK, const std::string &SK)
{

    std::string access_token_url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials";
    CURL *curl;

    CURLcode result_code;

    int error_code = 0;

    curl = curl_easy_init();

    if (curl)
    {

        std::string url = access_token_url + "&client_id=" + AK + "&client_secret=" + SK;

        curl_easy_setopt(curl, CURLOPT_URL, url.data());

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

        std::string access_token_result;

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &access_token_result);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->callback_token);

        result_code = curl_easy_perform(curl);

        if (result_code != CURLE_OK)
        {

            fprintf(stderr, "curl_easy_perform() failed: %s\n",

                    curl_easy_strerror(result_code));

            return 1;
        }

        access_token = access_token_result;

        curl_easy_cleanup(curl);

        error_code = 0;
    }
    else
    {

        fprintf(stderr, "curl_easy_init() failed.");

        error_code = 1;
    }

    return error_code;
}

/**
 * curl发送http请求调用的回调函数，回调函数中对返回的json格式的body进行了解析，解析结果储存在全局的静态变量当中
 * @param 参数定义见libcurl文档
 * @return 返回值定义见libcurl文档
 */
size_t BaiduDeploy::callback_result(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string s((char *)ptr, size * nmemb);

    std::string *json_result = static_cast<std::string *>(stream);

    *json_result = s;

    // std::string json_result(reinterpret_cast<const char *>(ptr), size * nmemb);

    // *(reinterpret_cast<std::ostringstream*>(stream)) << json_result;

    return size * nmemb;
}

/**
 * 调用对话接口，返回int格式的结果，具体格式解析见百度大脑文档
 * @param json_result 以string格式返回的json格式的结果
 * @param json_request_body 以string格式传递的json数据（如：{"log_id":"UNITTEST_10000","version":"2.0","service_id":"S10000","session_id":"","request":{"query":"你好","user_id":"88888"},"dialog_state":{"contexts":{"SYS_REMEMBERED_SKILLS":["1057"]}}}; // json格式 ）
 * @param access_token 以string格式传入的access token数据，access token获取方式见access_token获取相关文档及代码
 * @return 调用成功返回0，发生错误返回其他错误码
 */
int BaiduDeploy::unit_utterance(std::string &json_result, const std::string json_request_body,
                                const std::string &access_token)
{
    std::string url = get_utterance_url + "?access_token=" + access_token;
    LOG(INFO) << "url :" << url;

    CURL *curl = NULL;

    CURLcode result_code;

    int is_success = 0;

    curl = curl_easy_init();

    if (curl)
    {

        curl_easy_setopt(curl, CURLOPT_URL, url.data());

        curl_easy_setopt(curl, CURLOPT_POST, 1);

        curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_request_body.data());

        std::string access_token_result;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &access_token_result);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->callback_result);

        result_code = curl_easy_perform(curl);

        if (result_code != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result_code));
            cout << "error code " << result_code << endl;
            is_success = 1;
            return is_success;
        }
        json_result = access_token_result;
        curl_easy_cleanup(curl);
        is_success = 0;
    }
    else
    {
        fprintf(stderr, "curl_easy_init() failed.");
        is_success = 1;
    }
    return is_success;
}

int BaiduDeploy::get_errorcode(string &str)
{
    try
    {
        Json::Reader Reader;
        Json::Value DevJson;

        if (Reader.parse(str, DevJson))
        {
            return DevJson["error_code"].asInt();
        }
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << e.what();
    }
    return -1;
}

std::string BaiduDeploy::get_error_msg(string &str)
{
    try
    {
        Json::Reader Reader;
        Json::Value DevJson;
        if (Reader.parse(str, DevJson))
        {
            return DevJson["error_msg"].asString();
        }
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << e.what();
    }
    return "";
}

bool BaiduDeploy::set_deploymentId(string &str)
{
    try
    {
        Json::Reader Reader;
        Json::Value DevJson;
        Json::Value root;
        int deploymentid;
        if (Reader.parse(str, DevJson))
        {
            deploymentid = atoi(DevJson["result"]["deploymentId"].asString().c_str());
        }
        else
        {
            return false;
        }
        {

            ifstream is("./DeploymentInfo", std::ios::binary);
            if (!is.is_open())
                return false;
            bool changed = false;
            if (Reader.parse(is, root))
            {
                for (int i = 0; i < static_cast<int>(root.size()); i++)
                {
                    if (root[i]["botid"] == m_botid)
                    {
                        root[i]["deploymentid"] = deploymentid;
                        changed = true;
                        break;
                    }
                }
            }
            if (!changed)
            {
                Json::Value params;
                params["deploymentid"] = deploymentid;
                params["botid"] = m_botid;
                root.append(params);
            }
            is.close();
        }
        Json::StyledWriter sw;
        ofstream os;
        os.open("./DeploymentInfo");
        os << sw.write(root);
        os.close();
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << e.what();
    }
    return true;
}

int BaiduDeploy::get_deploymentId(int botid)
{
    int deploymentid = -1;
    try
    {
        Json::Reader reader;
        Json::Value root;
        //从文件中读取
        ifstream is;
        is.open("./DeploymentInfo", std::ios::binary);
        if (reader.parse(is, root))
        {
            for (int i = 0; i < static_cast<int>(root.size()); i++)
            {
                if (root[i]["botid"].asInt() == botid)
                {
                    deploymentid = root[i]["deploymentid"].asInt();
                    break;
                }
            }
        }
        is.close();
        return deploymentid;
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << e.what();
    }
    return deploymentid;
}

bool BaiduDeploy::inital()
{
    try
    {
        Json::Reader reader;
        Json::Value root;
        //从文件中读取
        ifstream is;
        is.open("./baidu_conf.json", std::ios::binary);
        if (reader.parse(is, root))
        {
            this->m_botid = root["botId"].asInt();
            this->m_region = root["region"].asString();
            this->m_model = root["version"].asString();
            return true;
        }
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << e.what();
    }
    return false;
}
