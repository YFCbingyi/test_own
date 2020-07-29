/*************************************************************************
	> File Name: test.cpp
    > Author: 
    > Mail: 
    > Created Time: 2020年05月25日 星期一 12时41分04秒
    ************************************************************************/

#include<iostream>
#include <chrono>
#include "ThreadPool.h"
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
using namespace std;

class A{
public:
    A() {}
    ~A(){}
    static size_t SaveWebsiteHtmlData(void *p_data, size_t size, size_t nmemb, void *stream)
    {
    if ((p_data == nullptr) || (stream == nullptr))
    {
        return 0;
    }
    *(reinterpret_cast<std::string *>(stream)) += std::string((char *)p_data, size * nmemb);

    return size * nmemb;
    }


    static void getHtmlData(const std::string &url, std::string &result)
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
                result = oss_website_html_data;
                std::cout << "get data " << std::this_thread::get_id() << std::endl;
                shishi = 0;
            }
            curl_easy_cleanup(p_curl);
        }
    }

    std::cout << "finish" << std::endl;
    std::cout << "最后" << std::endl;

    curl_global_cleanup();
    }


};

int main() {
	ThreadPool thread_pool(3);
	thread_pool.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::string url = "www.baidu.com";
	for(int i = 0; i < 100; i++) {
        std::string result;
        thread_pool.appendTask(std::bind(A::getHtmlData,url,result));
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << " i "<< i << std::endl;
	}

	thread_pool.stop();

	return 0;
}
