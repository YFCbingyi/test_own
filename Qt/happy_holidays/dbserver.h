#ifndef DBSERVER_H
#define DBSERVER_H
#include <sqlite3.h>
#include <iostream>

using namespace std;
class DBserver
{
public:
    static DBserver *getInstance() {
        return &db_;
    }
    bool init(std::string &path);
private:
    DBserver() {cout <<"db构造"<<endl;}
    ~DBserver() {cout <<"db析构"<<endl;}
    static DBserver db_;
private:
    std::string db_path_;

};

#endif // DBSERVER_H
