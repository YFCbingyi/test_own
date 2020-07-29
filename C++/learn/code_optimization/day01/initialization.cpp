/***************************************************
@File Name : initialization.cpp
@Project : 列表初始化
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-07-29 11:04:56
****************************************************/

#include <iostream>
#include <type_traits>

using namespace std;

struct Func
{
    public:
    Func(double a,int b) {
        x = a; y = b;
    }
        double x;
        int y;   
    /* data */
};

Func function() {
    return {1.2,10};
}

int main(int argc,char **argv)
{
    //1 普通数组
    int i_arr[3] = {1,2,3};

    //2 POD（plain old data）类型  Plain表示普通类型 old表示它是旧的与C语言兼容
    // 简单来说 POD类型就是可以直接使用memcpy复制的对象
    struct A
    {
        int x;
        struct B
        {
            int i;
            int j;
        } b;
        
    } a = {1, {2,3}};
    cout << std::boolalpha;
    cout << "A " <<std::is_pod<A>::value << endl;

    //3 拷贝初始化
    int i = 0;
    class Foo{
    public:
        Foo(int) {}
        int x;
    } foo = 122;    //需要拷贝构造函数

    //4 直接初始化
    int j(2);
    Foo bar(123);

    class Foo1{
        public:
        Foo1(int) {}
        private:
        Foo1(const Foo1 &); 
    };

    //5 
    Foo1 a1(123);
    // Foo1 a2 = a1; //‘main(int, char**)::Foo1::Foo1(const main(int, char**)::Foo1&)’ is private
    Foo1 a2{123};
    Foo1 a3 = {123}; //虽然使用了=，但是仍然是列表初始化，私有拷贝构造函数不会影响到它
    // 在初始化时，{}前面的等于号是否书写对于初始化行为没有影响


    //6 
    Func f = function();
    cout << f.x << f.y << endl;
    return 0;
}


