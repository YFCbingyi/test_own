#ifndef CLOUDSERVER_H
#define CLOUDSERVER_H

#include <iostream>
#include <string>

class CloudServer
{
public:
    CloudServer();
    
    std::string download_face_data();
};

#endif // CLOUDSERVER_H