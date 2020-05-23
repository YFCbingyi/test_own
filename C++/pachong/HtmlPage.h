#ifndef _HTMLPAGE_H_
#define _HTMLPAGE_H_

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <htmlcxx/html/ParserDom.h>
#include <htmlcxx/html/tree.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace htmlcxx;
class HtmlPage
{
private:
    /* data */
public:
    HtmlPage(std::string url) : mainhtml_(url) {}
    ~HtmlPage() {}

    static size_t SaveWebsiteHtmlData(void *p_data, size_t size, size_t nmemb, void *stream)
    {
        if ((p_data == nullptr) || (stream == nullptr))
        {
            return 0;
        }
        *(reinterpret_cast<std::string *>(stream)) += std::string((char *)p_data, size * nmemb);
        return size * nmemb;
    }
    static size_t DownloadFile(void *p_data, size_t size, size_t nmemb, void *stream)
    {
        if ((p_data == nullptr) || (stream == nullptr))
        {
            return 0;
        }

        std::ofstream *p_download_file = reinterpret_cast<std::ofstream *>(stream);
        p_download_file->write(reinterpret_cast<const char *>(p_data), size * nmemb);

        return size * nmemb;
    }

    void creatFolter(std::string &file, int index)
    {
        std::string cmd = "mkdir " + file + std::to_string(index);
        ::system(cmd.c_str());
    }

    void HtmlParse(std::string data)
    {
        htmlcxx::HTML::ParserDom parser;
        tree<HTML::Node> dom = parser.parseTree(data);
        // cout << dom << endl;
        title = "";
        for (auto t = dom.begin(); t != dom.end(); t++)
        {

            if (t->isTag())
            {
                t->parseAttributes();
                if (t->attribute("src").first && t->attribute("data-original").first && (t->attribute("src").second.find(".jpg") != std::string::npos))
                {
                    std::string hh = t->attribute("src").second;
                    std::cout << hh << std::endl;
                    DownData(title, pageIndex_, hh);
                }
            }
            else if (t->isComment())
            {
                // std::cout << t->text() << " is comment" << std::endl;
            }
            else
            {
                if (t->text().find(">  >") != std::string::npos)
                {
                    std::cout << "++++++++++++++++++++++++++++" << t->text() << std::endl;
                    title = t->text().substr(6, t->text().length());
                    // creatFolter(title, pageIndex_);
                }
                if ((t->text().find("共") != std::string::npos) && (t->text().find("页") != std::string::npos))
                {
                    std::string pa = t->text().substr(t->text().find("共") + 3, t->text().find("页") - 3);
                    pageCount_ = std::stoi(pa);
                    // std::cout << t->text().find("共")，t->text().find("页")；
                }
                // std::cout << t->text() << " is nothing" << std::endl;
            }
        }
    }

    void NextHtmlParse(std::string data)
    {
        htmlcxx::HTML::ParserDom parser;
        tree<HTML::Node> dom = parser.parseTree(data);
        // cout << dom << endl;
        for (auto t = dom.begin(); t != dom.end(); t++)
        {

            if (t->isTag())
            {
                t->parseAttributes();
                if (t->attribute("src").first && t->attribute("data-original").first && (t->attribute("src").second.find(".jpg") != std::string::npos))
                {
                    std::string hh = t->attribute("src").second;
                    std::cout << hh << std::endl;
                    DownData(title, pageIndex_, hh);
                }
            }
        }
    }

    void addHouzhui(std::string &str)
    {
        html_ = mainhtml_ + str;
    }

    void DownData(std::string title, int index, std::string url)
    {
        std::string file_name = url.substr(url.find_last_of('/') + 1);
        file_name = title + std::to_string(index) + "-" + file_name;
        std::cout << "download link: " << url << ", file name: " << file_name << "\n";
        std::ofstream download_file(file_name, std::ios_base::binary);
        CURL *p_curl = curl_easy_init();
        if (download_file.is_open())
        {
            // 下载图片
            curl_easy_setopt(p_curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(p_curl, CURLOPT_WRITEDATA, &download_file);
            curl_easy_setopt(p_curl, CURLOPT_WRITEFUNCTION, DownloadFile);
            CURLcode curl_code = curl_easy_perform(p_curl);
            if (curl_code != CURLE_OK)
            {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_code));
            }

            download_file.close();
        }
    }

    void GetData()
    {
        pageIndex_ = 1;
        std::cout << html_ << std::endl;
        curl_global_init(CURL_GLOBAL_ALL);
        int shishi = 3;
        while (shishi > 0)
        {
            CURL *p_curl = curl_easy_init();
            if (p_curl != nullptr)
            {
                // 保存网页html数据
                // std::ostringstream oss_website_html_data;
                std::string oss_website_html_data;
                curl_easy_setopt(p_curl, CURLOPT_URL, html_.c_str());
                curl_easy_setopt(p_curl, CURLOPT_WRITEDATA, &oss_website_html_data);
                curl_easy_setopt(p_curl, CURLOPT_WRITEFUNCTION, SaveWebsiteHtmlData);
                CURLcode curl_code = curl_easy_perform(p_curl);
                if (curl_code != CURLE_OK)
                {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_code));
                    shishi--;
                }
                else
                {
                    shishi = 0;
                    HtmlParse(oss_website_html_data);
                }
                curl_easy_cleanup(p_curl);
            }
            curl_global_cleanup();
        }

        pageIndex_++;
        for (; pageIndex_ <= pageCount_; pageIndex_++)
        {
            GetNextData(pageIndex_);
        }
        pageCount_ = 0;
    }

    void GetNextData(int index)
    {
        std::string relhtml = html_.substr(0, html_.length() - 5);
        relhtml = relhtml + "_" + std::to_string(index) + ".html";
        std::cout << relhtml << std::endl;
        curl_global_init(CURL_GLOBAL_ALL);

        int shishi = 3;
        while (shishi > 0)
        {
            CURL *p_curl = curl_easy_init();
            if (p_curl != nullptr)
            {
                // 保存网页html数据
                // std::ostringstream oss_website_html_data;
                std::string oss_website_html_data;
                curl_easy_setopt(p_curl, CURLOPT_URL, relhtml.c_str());
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
                    NextHtmlParse(oss_website_html_data);
                }
                curl_easy_cleanup(p_curl);
            }
        }

        curl_global_cleanup();
    }

private:
    //总页数
    int pageCount_;
    //当前页数
    int pageIndex_;
    //当前网站
    std::string mainhtml_;
    std::string html_;
    std::string title;
};
#endif