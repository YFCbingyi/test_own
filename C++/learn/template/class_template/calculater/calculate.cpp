/***************************************************
@File Name : calculate.cpp
@Project : 
@Author : chen bingyi 
@Mail : chenbingyi@riseauto.cn
@CreateTime :2020-07-29 16:59:38
****************************************************/

#include <iostream>

using namespace std;

template<typename T>

class Test{
private:
    T n;
    const T i;
public:
    Test() : i(0) {
        n = 12;
    }
    Test(T k);
    ~Test(){}

    void print();
    T operator+(T x);

};

template<typename T>
void Test<T>::print() {
    cout << "n = "<< n << endl;
    cout << "i = "<< i << endl;
}

template<typename T>
Test<T>::Test(T k) : i(k) {
    n = k;
}

template<typename T>
T Test<T>::operator+(T x) {
    return n + x;
}


int main(int argc,char **argv)
{
    Test<int> t1;
    cout << t1+2 << endl;

    Test<double> t2(8.7);
    t2.print();
    cout << t2+17 << endl;

    return 0;
}
