#include "my_string.h"
#include <exception>

my_string::my_string()
{

}
/*
 * func: 将src字符串根据split_string为关键拆分并得到一个vector容器
 * src: 源字符串
 * split_string: 关键字符串
 * return: vector容器
*/
std::vector<std::string> my_string::split_string(std::string src, const std::string &split_string) {
    try{
        std::vector<std::string> gstr;
        while(src.find_first_of(split_string) != std::string::npos) {
            gstr.push_back(src.substr(0,src.find_first_of(split_string)));
            src.erase(0,src.find_first_of(split_string)+split_string.length());
        }
        gstr.push_back(src);
        return gstr;
    }catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
/*
 * function:获取随机字符串,根据splitter分割res字符串
 * src: 完整字符串
 * splitter: 分隔符
 * return : 返回随机一个字符串
*/
std::string my_string::get_random_speech(std::string &src,std::string &splitter) {
    try {
        std::string str = src;
        std::string speech("");
        std::string sub = splitter;
        int num = 0;
        for (size_t i=0; (i=str.find(sub,i)) != std::string::npos; num++, i++) {
            std::cout << i << std::endl;
        }
        std::cout << "num " << num << std::endl;
        if(num == 0) {
            speech = str;
            return speech;
        }
        int rande = get_random_number(0,num+1)+1;
        int count = 0;
        size_t begin = -1;
        for(int i = 0 ; i < num ;i++) {
            while((begin=str.find(sub,begin+1))!=std::string::npos) {
                speech = str.substr(0,begin);
                str = str.substr(begin+3,str.length());
            }
            count++;
            if(rande == count) {
                return speech;
            }
        }
        count++;
        if(rande == count) {
            speech = str;
            return speech;
        }
        return speech;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
/*
 * func: 获取完整的字符串
 * src:源字符串
 * tem:暂存，将被其他代替
 * sub:替代字符串
*/
std::string my_string::get_full_speech(std::string &src,const std::string &tem,std::string &sub) {
    std::string res;
    if(src.find(tem.c_str()) != std::string::npos) {
        src.replace(src.find(tem.c_str()),tem.length(),sub);
    }
    res = src;
    return res;
}
