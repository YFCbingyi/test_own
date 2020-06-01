/*************************************************************************
	> File Name: 4.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月01日 星期一 09时41分42秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include "../normal/normal.h"


int main() {

    std::string str = " 设计 而     ";

    std::cout << "before \'"<< str << "\'" << std::endl;

    trim(str);

    std::cout << "end \'"<<str <<"\'"<< std::endl;
    

    //std::string cmd = "rm -rf 12/";
    //runcmd(cmd);

    return 0;
}
