/***************************************************
@File Name : Class.cpp
@Project : 
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-08-13 17:46:25
****************************************************/

#include <iostream>

using namespace std;


class student
{
public:
    int a;
    int b;
};

int main(int argc,char **argv)
{
    //类的设计
    //1）站在设计和实现者的角度
    //2) 站在使用者的角度
    //3) 父类子类

    //对象的拷贝
    // 对象本身是可以拷贝的
    // 默认情况下，类对象的拷贝是每个成员变量逐个拷贝
    // 如果在类中定义适当的赋值运算符，就能够控制对象的拷贝行为

    //对于单参数的构造函数，一般都声明为explicit ，除非你有特殊原因
    student b;
    b.a = 10;
    b.b = 11;
    student a = b;
    student c(b);
    student d{b};
    student e = {b};
    cout << b.a << b.b << endl;
    cout << a.a << a.b << endl;
    cout << c.a << c.b << endl;

    int i1 = (12,14,5,6,16);
    cout << i1 << endl;
    
    return 0;
}
