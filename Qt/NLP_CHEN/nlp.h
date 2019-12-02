#ifndef NLP_H
#define NLP_H
#include <iostream>

#include <string>

#include <curl/curl.h>

#include <jsoncpp/json/json.h>
#include <QObject>
//namespace std {
//    class NLP;
//}
class NLP :public QObject
{
    Q_OBJECT
    enum tu_errorcode {TU_CODE_ZERO = 0, TU_CODE_ERROR = 89};
public:
    NLP(QObject *parent = 0);
    ~NLP();
    static size_t tu_callback(void *ptr, size_t size, size_t nmemb, void *stream);
    int tu_unit_utterance( const std::string json_request_body);

    int tu_send_data(std::string &str);
    int tu_organize_data(std::string &str,std::string &scr);
    int tu_rcv_data(std::string &str);
    int tu_start(std::string &text);
    int tu_get_error_code(std::string &str);
    int tu_error_handle(int error_num);
    int tu_check_error_code(std::string &str);
    void tu_analysis(std::string str);
    bool get_mac_address_by_system(std::string & mac_address);
    static void parse_mac_address(const char * file_name, const char * match_words, std::string & mac_address);

private:
    std::string userid;
    const std::string apikey = "cbdd86e85f974130b5cac506c4efab10";
    QObject* m_parent;
signals:
    void send_result_(const QString &msg);
};


#endif // NLP_H
