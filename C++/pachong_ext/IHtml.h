#ifndef _IHTML_H_
#define _IHTML_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <htmlcxx/html/ParserDom.h>
#include <htmlcxx/html/tree.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace htmlcxx;

class IHtml
{
public:
    IHtml(/* args */);
    ~IHtml();

    static size_t SaveWebsiteHtmlData(void *p_data, size_t size, size_t nmemb, void *stream)
    {
        if ((p_data == nullptr) || (stream == nullptr))
        {
            return 0;
        }

        *(reinterpret_cast<std::string *>(stream)) += std::string((char *)p_data, size * nmemb);

        return size * nmemb;
    }

    // 保存要下载的数据
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

    void getHtmlData(const std::string &url, std::string &result)
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
                }
                curl_easy_cleanup(p_curl);
            }
        }

        std::cout << "finish" << std::endl;
        std::cout << "最后" << std::endl;

        curl_global_cleanup();
    }

    void download(const std::string &url, const std::string &path)
    {
        
        std::ofstream download_file(path, std::ios_base::binary);
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
        curl_easy_cleanup(p_curl);
    }
};

#endif