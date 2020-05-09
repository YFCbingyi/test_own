#ifndef _RECVTHREAD_H_
#define _RECVTHREAD_H_

#include "../../ThreadBase.h"

class RecvThread : public ThreadBase
{
private:
    /* data */
    int socketfd;
public:
    RecvThread(int socket) : socketfd(socket) {start();}
    ~RecvThread() {}
    void run();

};


#endif