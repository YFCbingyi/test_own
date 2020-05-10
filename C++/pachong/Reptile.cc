#include "Reptile.h"
#include "curl/curl.h"
#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <htmlcxx/html/tree.h>
#include <htmlcxx/html/ParserDom.h>
using namespace htmlcxx;
using namespace std;

Reptile::Reptile(/* args */)
{
}

Reptile::~Reptile()
{
}

void Reptile::start(const std::string &url)
{
    mainHtml_ptr_ = std::make_shared<HtmlPage>(url);
    simHtml_ptr_ = std::make_shared<HtmlPage>(url);
    GetHtmlData(url);
}

size_t Reptile::SaveWebsiteHtmlData(void *p_data, size_t size, size_t nmemb, void *stream)
{
    if ((p_data == nullptr) || (stream == nullptr))
    {
        return 0;
    }

    // cout << *(char *)p_data << endl;
    // std::string a = ;
    // cout << a << endl;
    *(reinterpret_cast<std::string *>(stream)) += std::string((char *)p_data, size * nmemb);

    // std::string html_data(reinterpret_cast<const char*>(p_data), size * nmemb);
    // *(reinterpret_cast<std::ostringstream*>(stream)) << html_data;
    return size * nmemb;
}

// 保存要下载的数据
size_t Reptile::DownloadFile(void *p_data, size_t size, size_t nmemb, void *stream)
{
    if ((p_data == nullptr) || (stream == nullptr))
    {
        return 0;
    }

    std::ofstream *p_download_file = reinterpret_cast<std::ofstream *>(stream);
    p_download_file->write(reinterpret_cast<const char *>(p_data), size * nmemb);

    return size * nmemb;
}

void Reptile::ParserMainHtml(const std::string &data)
{
    // ofstream file;
    // file.open("name.txt");
    // file << data << endl;
    // file.close();
    htmlcxx::HTML::ParserDom parser;
    tree<HTML::Node> dom = parser.parseTree(data);
    // cout << dom << endl;

    for (auto t = dom.begin(); t != dom.end(); t++)
    {
        if (t->isTag())
        {
            // std::cout << t->text() << " is tag" << std::endl;
            t->parseAttributes();
            if (!t->attribute("href").first)
            {
                continue;
            }
            if (t->attribute("href").second.find(".html") != std::string::npos && t->attribute("href").second.find("manhua") != std::string::npos)
            {
                std::string hh = t->attribute("href").second;
                // std::cout << hh.substr(13,hh.length()) << std::endl;
                std::string houzhui = hh.substr(13,hh.length());
                simHtml_ptr_->addHouzhui(houzhui);
                simHtml_ptr_->GetData();
                break;
            }
        }
        else if (t->isComment())
        {
            // std::cout << t->text() << " is comment" << std::endl;
        }
        else
        {
            // std::cout << t->text() << " is nothing" << std::endl;
        }
    }
}
// std::cout <<"-->" <<t->text() << std::endl;
// if (t->text().find("downButton") != std::string::npos || t->text().find(".rar") != std::string::npos)
// {
//     t->parseAttributes();
//     if(!t->attribute("class").first || !t->attribute("href").first)
//     {
//         continue;
//     }
//     if(t->attribute("class").second == "downButton") {
//         std::string hh = t->attribute("href").second;
//         std::cout << hh << endl;
//     }
// }
// else
// {

// }

// if(strcasecmp(t->tagName().c_str(), "h1") == 0) {
//     t+=1;
//     std::cout << t->text() << std::endl;
//     if(t->isComment()) {
//         std::cout << "is comment" << std::endl;
//     }
//     if(t->isTag()) {
//         std::cout << "is tag "<< std::endl;
//     }
// }

void Reptile::GetHtmlData(const std::string &url)
{
    curl_global_init(CURL_GLOBAL_ALL);
    std::string website_url = url;

    CURL *p_curl = curl_easy_init();
    if (p_curl != nullptr)
    {
        // 保存网页html数据
        // std::ostringstream oss_website_html_data;
        std::string oss_website_html_data;
        curl_easy_setopt(p_curl, CURLOPT_URL, website_url.c_str());
        curl_easy_setopt(p_curl, CURLOPT_WRITEDATA, &oss_website_html_data);
        curl_easy_setopt(p_curl, CURLOPT_WRITEFUNCTION, SaveWebsiteHtmlData);
        CURLcode curl_code = curl_easy_perform(p_curl);
        if (curl_code != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_code));
        }
        else
        {
            ParserMainHtml(oss_website_html_data);
        }
        curl_easy_cleanup(p_curl);
    }

    std::cout << "finish" << std::endl;
    std::cout << "最后" << std::endl;

    curl_global_cleanup();
}