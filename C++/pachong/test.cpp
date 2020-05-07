/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020�?05�?06�? 星期�? 17�?17�?18�?
 ************************************************************************/

using namespace std;

#define CURL_STATICLIB
// #include "libcurl/inlcude/curl.h"
#include "curl/curl.h"
#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
 
// 保存网页的html数据
size_t SaveWebsiteHtmlData(void * p_data, size_t size, size_t nmemb, void * stream)
{
    if ((p_data == nullptr)
        || (stream == nullptr))
    {
        return 0;
    }
 
    std::string html_data(reinterpret_cast<const char*>(p_data), size * nmemb);
    *(reinterpret_cast<std::ostringstream*>(stream)) << html_data;
    return size * nmemb;
}
 
// 保存要下载的数据
size_t DownloadFile(void * p_data, size_t size, size_t nmemb, void * stream)
{
    if ((p_data == nullptr)
        || (stream == nullptr))
    {
        return 0;
    }
 
    std::ofstream *p_download_file = reinterpret_cast<std::ofstream*>(stream);
    p_download_file->write(reinterpret_cast<const char*>(p_data), size * nmemb);
 
    return size * nmemb;
}
 
int mainmmm()
{
    // 初�?�化libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    std::string website_url = "";
    while (std::cin >> website_url)
    {
        CURL *p_curl = curl_easy_init();
        if (p_curl != nullptr)
        {
            // 保存网页html数据
            std::ostringstream oss_website_html_data;
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
                // 匹配图片的下载链�?
                std::regex regex_jpg("src=\"(.+?\\.jpg)\"");
                std::string website_html_data = oss_website_html_data.str();
                std::sregex_iterator sit(website_html_data.cbegin(), website_html_data.cend(), regex_jpg);
                std::sregex_iterator sit_end;
                for (; sit != sit_end; ++sit)
                {
                    std::string download_link = sit->str(1);
                    std::string file_name = download_link.substr(download_link.find_last_of('/') + 1);
                    std::cout << "download link: " << download_link << ", file name: " << file_name << "\n";
                    std::ofstream download_file(file_name, std::ios_base::binary);
                    if (download_file.is_open())
                    {
                        // 下载图片
                        curl_easy_setopt(p_curl, CURLOPT_URL, download_link.c_str());
                        curl_easy_setopt(p_curl, CURLOPT_WRITEDATA, &download_file);
                        curl_easy_setopt(p_curl, CURLOPT_WRITEFUNCTION, DownloadFile);
                        curl_code = curl_easy_perform(p_curl);
                        if (curl_code != CURLE_OK)
                        {
                            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_code));
                        }
 
                        download_file.close();
                    }
                    
                }
            }
            curl_easy_cleanup(p_curl);
        }
 
        std::cout << "finish" << std::endl;
    }
 
    curl_global_cleanup();
    return 0;
}