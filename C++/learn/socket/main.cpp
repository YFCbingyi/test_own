/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年01月16日 星期四 13时44分44秒
 ************************************************************************/

#include<iostream>
using namespace std;

#include"Server.h"
#include"Client.h"

int main(int argc, char *argv[]) {
    myClient mc;
    std::string ip = "127.0.0.1";
    if(!mc.start(ip,10100)) {
        return -1;
    }
    while(true) {
        char str[20];
        std::cin>>str;
        std::string data = str;
        if(data.compare("quit") == 0) {
            break;
        }
        mc.sendData(data);
    }
    return 0;
}
