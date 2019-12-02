#ifndef TULING_H
#define TULING_H

#include <string>
#include <atomic>
#include "nlpbase.h"

class Tuling : public NlpBase
{
public:
    Tuling();
    virtual void start_(std::string &qus);
private:
    static size_t tu_callback(void *ptr, size_t size, size_t nmemb, void *stream);
    int unit_utterance(std::string &json_result, const std::string json_request_body);
    void thd_timeout_func(std::string &qus);
    std::string const organization_message(std::string &text);
    int tu_rcv_data(std::string &str);
    int tu_get_error_code(std::string &str);
    int tu_check_error_code(std::string &str);

    void tu_analysis(std::string str);
private:
    const std::string apikey;
    std::atomic<bool> m_taskfinished;


};

#endif // TULING_H
