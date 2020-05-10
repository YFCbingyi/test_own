#ifndef _REPTILE_H_
#define _REFTILE_H

#include <iostream>
#include <string>
#include <memory>

#include "HtmlPage.h"
class Reptile
{
private:
    /* data */
public:
    Reptile();
    ~Reptile();

    void start(const std::string &url);

    static size_t SaveWebsiteHtmlData(void * p_data, size_t size, size_t nmemb, void * stream);
    static size_t DownloadFile(void * p_data, size_t size, size_t nmemb, void * stream);
private:
    void GetHtmlData(const std::string &url);
    void ParserMainHtml(const std::string &data);

    std::shared_ptr<HtmlPage> mainHtml_ptr_;
    std::shared_ptr<HtmlPage> simHtml_ptr_;
};

#endif