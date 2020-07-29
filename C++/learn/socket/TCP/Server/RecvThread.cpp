#include "RecvThread.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <strings.h>

void RecvThread::run()
{
    char buf[1024] = "";
    while (!terminate)
    {
        ::bzero(buf, sizeof(buf));
        int size = ::recv(socketfd, buf, sizeof(buf) - 1, 0);
        if (size > 0)
        {
            std::string msg = buf;
            std::cout << "recv msg : " << msg << std::endl;
        }
    }
}