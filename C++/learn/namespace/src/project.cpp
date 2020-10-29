/***************************************************
@File Name : project.cpp
@Project : 命名空间
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-07-31 11:39:56
****************************************************/
#include <iostream>

#include "project.h"

//张三
namespace zhangsan
{
    void radius()
    {
        std::cout << "张三" << std::endl;
    }
} // namespace zhangsan

//李四
namespace lisi
{
    void radius()
    {
        std::cout << "李四" << std::endl;
    }
} // namespace lisi

int main(int argc, char **argv)
{
    zhangsan::radius();
    lisi::radius();
    lisi::radius2();
    return 0;
}
