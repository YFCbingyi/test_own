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

    cout << dom.size() << endl;
    for (auto t = dom.begin(); t != dom.end(); t++)
    {
        t->parseAttributes();
        if (t->isTag())
        {
            if (!t->attribute("href").first)
            {
                continue;
            }
            if (t->attribute("href").second.find(".html") != std::string::npos && t->attribute("href").second.find("manhua") != std::string::npos)
            {
                std::string hh = t->attribute("href").second;
                std::string houzhui = hh.substr(13, hh.length());
                std::cout << houzhui << std::endl;
                simHtml_ptr_->addHouzhui(houzhui);
                simHtml_ptr_->GetData();
                break;
            }
        }
        else if (t->isComment())
        {
        }
        else
        {
        }
    }
}

void Reptile::GetHtmlData(const std::string &url)
{
    curl_global_init(CURL_GLOBAL_ALL);
    std::string website_url = url;

    int shishi = 3;
    while (shishi > 0)
    {
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
                shishi--;
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_code));
            }
            else
            {
                shishi = 0;
                ParserMainHtml(oss_website_html_data);
            }
            curl_easy_cleanup(p_curl);
        }
    }

    std::cout << "finish" << std::endl;
    std::cout << "最后" << std::endl;

    curl_global_cleanup();
}