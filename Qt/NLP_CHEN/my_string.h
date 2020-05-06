#ifndef MY_STRING_H
#define MY_STRING_H

#include<iostream>
#include <vector>
#define RS_ROBOT "RS_DATA"
#include "testbase.h"

class my_string : public TestBase
{
public:
    my_string();
    enum RobotType {
        T_XIAORUI,
        T_XIAOXUE,
        T_ALICE,
        T_DEFAULT
    };

    void test() {
        std::string win = "B01";
        std::string winn = "B01_ 社会保险";
        getWindowName(win,winn);
        std::cout << winn << std::endl;
    }
private:
    void getWindowName(const std::string &str,std::string &src);
    
private:
    bool isWindowNo(std::string &str) {
        if(str.size() < 2) 
            return false;
        for(int i = 0; i < str.size() ; i++) {
            if(i == 0) {
                if(!(str[i] >= 'A' && str[i] <= 'Z'))
                    return false;
            } else {
                if(!(str[i] >= '0' && str[i] <= '9'))
                    return false;
            }
        }
        return true;
    }
    
private:
    int get_random_number(int min,int max){
        return rand() % static_cast<int>(max + 1 - min) + min;
    }
    std::vector<std::string> split_string(std::string src,const std::string &split_string);
    std::string get_random_speech(std::string &src,std::string &splitter);
    std::string get_full_speech(std::string &src,const std::string &tem,std::string &sub);

private:
    enum RobotType robot_type();
};

#endif // MY_STRING_H
