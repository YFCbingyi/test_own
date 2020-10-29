/***************************************************
@File Name : main.cpp
@Project : 
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-31 15:00:53
****************************************************/

#include <iostream>
#include <cstring>

#include "DBServer.h"

using namespace std;

int main(int argc,char **argv)
{
    if(argc != 5) {
        cerr << "格式有误" << endl;
        return -1;
    } 
    //读取数据库
    DBServer db("./govhall.db");

    //获取argv的值，知道修改的是哪一个区域，且了解对应的xy偏移
    std::string start = argv[1];
    int istart = std::stoi(start) -1;
    cout << istart << endl;
    std::string end = argv[2];
    int iend = std::stoi(end) +1;
    cout << iend << endl;
    std::string posx = argv[3];
    int ix = std::stoi(posx);
    cout << ix << endl;
    std::string posy = argv[4];
    int iy = std::stoi(posy);
    cout << iy << endl;
    // cout << arg?v[1] << endl;
    // cout << argv[2] << endl;
    // cout << argv[3] << endl;
    //获取该区域的点的集合，获取一个修改一个

    return 0;
}

