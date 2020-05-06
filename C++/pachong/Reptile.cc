#include "Reptile.h"
#include "curl/curl.h"
#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

Reptile::Reptile(/* args */)
{
}

Reptile::~Reptile()
{
}

void Reptile::start(const std::string &url) {
    GetHtmlData(url);
}

size_t Reptile::SaveWebsiteHtmlData(void * p_data, size_t size, size_t nmemb, void * stream)
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
size_t Reptile::DownloadFile(void * p_data, size_t size, size_t nmemb, void * stream)
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

void Reptile::GetHtmlData(const std::string &url)
{
    curl_global_init(CURL_GLOBAL_ALL);
    std::string website_url = url;


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
                
                // 匹配图片的下载链接
                std::regex regex_jpg("class=\"showtxt\"");
                std::string website_html_data = oss_website_html_data.str();

                std::string file_name = "logg";
                std::ofstream download_file(file_name, std::ios_base::out);
                {                    
                    if (download_file.is_open())
                    {
                        // 下载图片
                        curl_easy_setopt(p_curl, CURLOPT_URL, website_url.c_str());
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

    curl_global_cleanup();
}