/*************************************************************************
	> File Name: target_type.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月12日 星期五 10时19分13秒
 ************************************************************************/

#include<iostream>
#include<functional>

using namespace std;

int f(int a){return -a;}

int main() {
    
    std::function<int(int)> fn1(f),
                            fn2([](int a){return -a;});

    cout << fn1.target_type().name() << '\n'
    << fn2.target_type().name() << '\n';
    return 0;
}
