/*************************************************************************
	> File Name: 3.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年05月29日 星期五 11时05分35秒
 ************************************************************************/

#include<iostream>
using namespace std;

class A{
public:
    A(){
        std::cout << "A" << std::endl;
    }
    ~A(){
        std::cout << "~A" << std::endl;
    }
    static void load();
    static std::string str;
};

std::string A::str;

void A::load() {
    str = "good";
}

int main() {

    A::load();
    
    std::cout << " str "<< A::str << std::endl;

    return 0;
}
