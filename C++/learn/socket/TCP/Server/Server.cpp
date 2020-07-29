/*************************************************************************
	> File Name: Server.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年01月16日 星期四 13时36分27秒
 ************************************************************************/

#include <iostream>
#include "Server.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <unistd.h>
#include <strings.h>
#include <exception>
myServer::myServer()
{
}

myServer::~myServer()
{
    if (socketfd_ > 0)
    {
        close(socketfd_);
    }
}

bool myServer::get_socket(int port)
{
    try
    {
        struct sockaddr_in my_addr;    /* my address information */
        struct sockaddr_in their_addr; /* connector's address information */
        int sockfd;
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            std::cerr << " socket error " << std::endl;
            return false;
        }
        std::cout << " socket ok" << std::endl;
        my_addr.sin_family = AF_INET;         /* host byte order */
        my_addr.sin_port = htons(port);       /* short, network byte order */
        my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
        bzero(&(my_addr.sin_zero), 0);        /* zero the rest of the struct */
        if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
        {
            std::cerr << " bind error " << std::endl;
            return false;
        }
        std::cout << " bind ok" << std::endl;
        if (listen(sockfd, BACKLOG) == -1)
        {
            std::cerr << " listen error " << std::endl;
            return false;
        }
        std::cout << " listen ok" << std::endl;
        socklen_t sin_size;
        sin_size = sizeof(struct sockaddr_in);
        if ((socketfd_ = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
        {
            std::cerr << " accept error " << std::endl;
            return false;
        }
        std::cout << " accept ok" << std::endl;
        if (socketfd_ > 0)
        {
            return true;
        }
        return false;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

bool myServer::start(int port)
{
    std::cout << "start " << std::endl;
    if (get_socket(port))
    {
        std::cout << "connect ok" << std::endl;
        rec_ptr_ = std::make_shared<RecvThread>(socketfd_);
    }
    while (true)
    {
        /* code */
    }
}
bool myServer::sendData(std::string &data)
{
    if (send(socketfd_, data.c_str(), data.length(), 0) == -1)
    {
        std::cout << "send error" << std::endl;
        return false;
    }
    return true;
}

void myServer::thd_recv()
{
    std::cout << "recv thread" << std::endl;
    char buf[1024];
    while (true)
    {
        bzero(buf, sizeof(buf));
        int size = ::recv(socketfd_, buf, sizeof(buf) - 1, 0);
        if (size > 0)
        {
            std::string msg = buf;
            std::cout << "recv msg : " << msg << std::endl;
        }
    }
}

int main(int argc, char **argv)
{
    int port = 8000;
    if (argc == 2)
    {
        port = std::stoi(std::string(argv[1]));
    }
    myServer server;
    server.start(port);
    return 0;
}
