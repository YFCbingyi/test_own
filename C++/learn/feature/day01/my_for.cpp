/***************************************************
@File Name : my_for.cpp
@Project : 
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-06 11:21:18
****************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    int my_array[5] = {1, 2, 3, 4, 5};
    // 每个数组元素乘于 2
    for (int &x : my_array)
    {
        x *= 2;
        cout << x << endl;
    }
    // auto 类型也是 C++11 新标准中的，用来自动获取变量的类型
    for (auto &x : my_array)
    {
        x *= 2;
        cout << x << endl;
    }

    return 0;
}
