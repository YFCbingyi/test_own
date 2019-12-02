#ifndef NLPBASE_H
#define NLPBASE_H
#include <string>
#include <jsoncpp/json/json.h>
#include <atomic>
#include <thread>
class NlpBase
{
public:
    NlpBase();
    virtual bool init() {return true;}
    virtual void start_(std::string &qus) = 0;
    int get_end_result_msg(std::string &rcv);
    int error_handle(int error_num);
    int get_random_number(int min,int max) const {
        return rand() % static_cast<int>(max + 1 - min) + min;
    }
    bool initial();
private:
    void load_config();
    void set_userid();
    int filt_text(std::string &str);

public:
    enum {CODE_ZERO = 0, CODE_NOT_USE,CODE_GET_TOKEN,CODE_RESEND,CODE_EMPTY,CODE_NONETWORK,ERROR_TYPE = 88,TU_CODE_ERROR = 89};
    std::string m_userid;
    std::string m_version;
    std::string m_region;
    int m_timeout;
    int m_botid;
    std::atomic<bool> support_tu_api;
    std::string msg_end_result;
    std::thread::id thread_id_;
    std::atomic<bool> m_taskfinished;
private:
    const std::string en_symbol[4];
    const std::string ch_symbol[4];
};

#endif // NLPBASE_H
