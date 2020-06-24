/*************************************************************************
	> File Name: operator_brackets.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月11日 星期四 16时21分20秒
 ************************************************************************/

#include<iostream>
#include<functional>
/*
 *  std::function<R(args...)>::operator()
 *  以参数 args 调用存储的可调用函数目标。等效于进行 INVOKE<R>(f, std::forward<Args>(args)...) ，其中 f 是 *this 的目标对象，且 INVOKE 是描述于可调用 (Callable) 的操作。
 *  参数
 *  args 传递给存储的可调用函数目标的参数
 *  返回值
 *  若R为void，则为无。否则为存储的可调用对象的调用返回值
 *  异常
 *  若不存储可调用函数目标，即 !*this == true ，则抛出 std::bad_function_call
* */

using namespace std;

void call(std::function<int()> f) {
    cout << f() << endl;
}

int normal_function() {
    return 42;
}

int main() {
    int n =1;
    std::function<int()> f = [&n](){ return n; };
    call(f);

    n = 2;
    call(f);

    f = normal_function;
    call(f);

    return 0;
}
