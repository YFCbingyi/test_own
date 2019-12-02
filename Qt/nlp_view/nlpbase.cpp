#include "nlpbase.h"
#include "debug_log.h"
#include <iostream>
#include <exception>
#include <sstream>
#include <unistd.h>
NlpBase::NlpBase() : en_symbol({"?",".","!",","}),ch_symbol({"？","。","！","，"}) {

}

bool NlpBase::initial() {
    this->load_config();
    this->set_userid();
    for(int i = 0;i<4;i++) {
        std::cout << en_symbol[i] << std::endl;
    }
    for(int i = 0;i<4;i++) {
        std::cout << ch_symbol[i] << std::endl;
    }
    return true;
}

void NlpBase::load_config()
{
//    char *conf;
//    conf = getenv(RS_CONF);
    char *conf = "/home/cby/rsData/conf";
    if(conf == NULL) {
        std::cout << "NlpFunc::load_config : RS_CONF is not find" << std::endl;
    }
    //初始化日志文件

    std::string log_info = std::string(conf) + "/../log/nlp_log_info";
    std::string log_warning = std::string(conf) + "/../log/nlp_log_warn";
    std::string log_error = std::string(conf) + "/../log/nlp_log_error";
    std::cout << " info " <<log_info
              << " warn " <<log_warning
              << " error " <<log_error
              <<std::endl;
//    initLogger(log_info,log_warning,log_error);

    Json::Reader reader;
    Json::Value root;
    //从文件中读取
    std::ifstream is;
//    std::string nlp_path_;
//    ros::param::param<std::string>("~nlp_path",nlp_path_,NLP_PATH);
    std::string nlp_path_ = std::string(conf) + "/voice/nlp.json";
    is.open(nlp_path_, std::ios::binary);
    LOG(INFO) << "nlp _path "<<nlp_path_;
    try {
        if(reader.parse(is,root)) {
            int num = 0;std::string text("");
            m_botid = (num = root["botId"].asInt()) > 0 ? num : 0;
            m_version = (text = root["version"].asString()).empty() ? "" : text;
            m_timeout = (num = root["time_out"].asInt()) > 0 ? num : 0;
            m_region = (text = root["region"].asString()).empty() ? "" : text;
            support_tu_api = root["support_tu"].asBool() ? true : false;
            if(support_tu_api) {
                LOG(INFO) << "NlpFunc::load_config : support tuling API";
            }
        }
    } catch(std::exception &e) {
        LOG(ERROR) << "NlpFunc::load_config : exception: "<<e.what();
    }
}

void NlpBase::set_userid() {
    try {
        char command[512] = { 0 };
        snprintf(command, sizeof(command), "lshw -c network | grep serial | head -n 1 > .lshw_.txt");
        if (0 == system(command)) {
            std::ifstream ifs(".lshw_.txt", std::ios::binary);
            if (!ifs.is_open()) {
                return;
            }
            char line[4096] = { 0 };
            while (!ifs.eof()) {
                ifs.getline(line, sizeof(line));
                if (!ifs.good()) {
                    break;
                }
                LOG(INFO) << "NlpFunc::set_userid : " <<line;
                std::string serial = line;
                std::string value = "serial:";
                int index = serial.find_first_of(value);
                if(index < serial.length()) {
//                    m_userid = serial.substr(index+value.length(),serial.length()-index-value.length());
//                    m_userid = "34:41:5d:7d:3c:1e";
                    m_userid = "88888";
                    LOG(INFO) << "NlpFunc::set_userid : m_userid "<<m_userid;
                    break;
                } else {
                    LOG(ERROR) << "NlpFunc::set_userid : not find value 'serial'";
                    m_userid = "88888";
                    break;
                }
            }
            unlink(".lshw_.txt");
        }
    } catch(std::exception &e) {
        LOG(ERROR) << "NlpFunc::set_userid : exception  "<<e.what();
    }
}

int NlpBase::filt_text(std::string &str)
{
    try {
        if(str.length() == 0) {
            return -1;
        }
        for(int i = 0; i < sizeof(en_symbol)/sizeof(en_symbol[0]);i++) {
            if(str.compare(en_symbol[i]) == 0 && str.length() == 1)	{
                str = "";
                return -1;
            }
            if(str.substr(str.length()-1).compare(en_symbol[i]) == 0) {
                str = str.substr(0,str.length()-1);
                return 1;
            }
        }
        for(int i = 0;i < sizeof(ch_symbol)/sizeof(ch_symbol[0]);i++) {
            if(str.compare(ch_symbol[i]) == 0 && str.length() == 3) {
                str = "";
                return -1;
            }
            if(str.substr(str.length()-3).compare(ch_symbol[i]) == 0) {
                str = str.substr(0,str.length()-3);
                return 1;
            }
        }
    } catch (std::exception &e) {
        LOG(ERROR)<<"NLP: exception " << e.what();
    }
    return 0;
}

int NlpBase::error_handle(int error_num) {
    Json::Value result;
    result["id"].resize(0);
    result["func"] = "";
    switch(error_num) {
    case CODE_NOT_USE:
        result["errorcode"] = CODE_NOT_USE;
        result["txt"] = "业务咨询功能暂时不可用";
        break;
    case CODE_GET_TOKEN:
        result["errorcode"] = CODE_GET_TOKEN;
        result["txt"] = "业务咨询功能暂时不可用";
        break;
    case CODE_RESEND:
        result["errorcode"] = CODE_RESEND;
        result["txt"] = "业务咨询功能暂时不可用";
        break;
    case ERROR_TYPE:
        result["errorcode"] = ERROR_TYPE;
        if(get_random_number(0,2) == 0)
            result["txt"] = "不好意思，我还无法回答这个问题，不过我会继续学习的。";
        else
            result["txt"] = "这个问题太难了，暂时我还不太会，你可以问问其他问题呢。";
        break;
    case CODE_EMPTY:
        result["errorcode"] = CODE_EMPTY;
        result["txt"] = "如果你什么都不说，我也不知道该怎么回答你";
    case CODE_NONETWORK:
        result["errorcode"] = CODE_ZERO;
        result["txt"] = "当前的网络信号实在太差啦，换个网络好的再试试呗。";
    case TU_CODE_ERROR:
        result["errorcode"] = TU_CODE_ERROR;
        result["txt"] = "我还在学习中，暂时不能回答你的问题";
        break;
    default:
        break;
    }
    msg_end_result = result.toStyledString();
    return 0;
}

int NlpBase::get_end_result_msg(std::string &rcv)
{
    rcv = msg_end_result;
    msg_end_result = "";
orginaze:
    if(!rcv.empty())
        return 0;
    else {
        LOG(INFO) << "NLP: end result msg is null" ;
        error_handle(ERROR_TYPE);
        rcv = msg_end_result;
        msg_end_result = "";
        goto orginaze;
    }
    return 1;
}

