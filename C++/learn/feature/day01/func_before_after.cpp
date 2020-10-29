/***************************************************
@File Name : func_before_after.cpp
@Project : 
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-06 11:38:02
****************************************************/

#include <iostream>

using namespace std;

void func1(int a,int) {
    cout << a << "\n";
    return;
}

auto func2(int a,int b) -> int {
    return a+b;
}

int main(int argc,char **argv)
{
    //1
    func1(12,13);
    //2
    cout << func2(12,13) << endl;

    return 0;
}
