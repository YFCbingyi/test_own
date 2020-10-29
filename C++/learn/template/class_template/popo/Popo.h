/***************************************************
@File Name: Popo.h
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-07-30 11:22:20
****************************************************/

#ifndef _POPO_H
#define _POPO_H

#include <vector>

template<typename T>
class Popo
{
private:
   std::vector<T> vecs_; 

public:
    Popo(/* args */);
    ~Popo();
    void push_back(T t) {
        vecs_.push_back(t);
    }
    void pop_back() {
        vecs_.pop_back();
    }
    bool is_empty() {

    }
};

Popo::Popo(/* args */)
{
}

Popo::~Popo()
{
}



#endif