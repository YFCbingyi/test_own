/*************************************************************************
	> File Name: Client.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年01月16日 星期四 13时58分50秒
 ************************************************************************/

#include "Client.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <string>
using namespace std;

myClient::myClient()
{
}

myClient::~myClient()
{
}

bool myClient::start(std::string &ip, int port)
{
    std::cout << "ready connect " << ip << " port " << port << i << std::endl;
    socket_ = get_client(ip, port);
    if (socket_ > 0)
    {
        return true;
    }
    return false;
}

bool myClient::sendData(std::string &data)
{
    if (send(socket_, data.c_str(), data.length(), 0) == -1)
    {
        return true;
    }
    return false;
}

int myClient::get_client(std::string &address, int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        return -1;
    }
    ::bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    ::inet_aton(address.c_str(), &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);
    if (::connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        close(sockfd);
        return -1;
    }
    return sockfd;
}

int main(int argc, char **argv)
{
    std::string ip("127.0.0.1");
    int port = 8000;
    if (argc == 3)
    {
        ip = argv[1];
        // std::string a = argv[2];
        port = std::stoi(std::string(argv[2]));
    }
    myClient client;
    client.start(ip, port);
    return 0;
}
