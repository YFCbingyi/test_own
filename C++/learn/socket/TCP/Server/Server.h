/*************************************************************************
	> File Name: Server.h
	> Author: 
	> Mail: 
	> Created Time: 2020年01月16日 星期四 13时33分58秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include <iostream>
#include <string>
#include <thread>
#define BACKLOG 10 /*多少等待连接控制*/
#include "RecvThread.h"
class myServer
{
public:
    myServer();
    ~myServer();
    bool start(int port);
    bool sendData(std::string &data);
private:
    bool get_socket(int port);
    void thd_recv();
private:
    int socketfd_;
    std::shared_ptr<RecvThread> rec_ptr_;
};
#endif
