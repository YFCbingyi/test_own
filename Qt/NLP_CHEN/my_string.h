#ifndef MY_STRING_H
#define MY_STRING_H

#include<iostream>
#include <vector>

class my_string
{
public:
    my_string();
    void start() {

        std::string str = "你好，%需要什么服务///天气怎么样///我叫%，你们知道吗///大河治水%来，带我";
//        std::string splitter = "///";
        std::vector<std::string> vv = split_string(str,std::string("///"));
        for(int i = 0 ; i < 5; i ++)
        {
        std::string src = vv[get_random_number(0,vv.size()-1)];
//        std::string src = get_random_speech(str,splitter);
        std::cout << src << std::endl;
//        std::string tem = "%";
        std::string sub = "帅哥";
        std::string rel = get_full_speech(src,std::string("%"),sub);
        std::cout << rel << std::endl;
        }
    }

private:
    int get_random_number(int min,int max){
        return rand() % static_cast<int>(max + 1 - min) + min;
    }
    std::vector<std::string> split_string(std::string src,const std::string &split_string);
    std::string get_random_speech(std::string &src,std::string &splitter);
    std::string get_full_speech(std::string &src,const std::string &tem,std::string &sub);
};

#endif // MY_STRING_H
