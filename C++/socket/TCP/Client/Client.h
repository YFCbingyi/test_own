/*************************************************************************
	> File Name: Client.h
	> Author: 
	> Mail: 
	> Created Time: 2020年01月16日 星期四 13时57分33秒
 ************************************************************************/

#ifndef _CLIENT_H
#define _CLIENT_H

#include <iostream>

class myClient
{
public:
    myClient();
    ~myClient();
    bool start(std::string &ip,int port);
    bool sendData(std::string &data);
private:
    int get_client(std::string &address,int port);

private:
    int socket_;
};
#endif
