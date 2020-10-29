/***************************************************
@File Name: DBServer.h
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-31 15:03:08
****************************************************/

#ifndef _DBSERVER_H
#define _DBSERVER_H

#include <string>
#include <sqlite3.h>
#include <vector>

class DBServer
{
private:
    /* data */
public:
    DBServer(const std::string &path);
    ~DBServer();

    bool fixData(int start,int end,int px,int py);
public:
    // using std::vector<float,float,float,float,float,float,float,float> pos;

    private:
    std::string path_;
};


#endif