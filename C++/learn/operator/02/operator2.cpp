/*************************************************************************
	> File Name: operator2.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月04日 星期四 09时39分41秒
    谓词函数通常用来对传进来的参数进行判断，并返回bool值，但是一般的函数形式固化，比如字符串长度比较只能判断是否大于一个确定的长度值。函数对象可以作为谓词函数，并可以在类初始化时传递参数，如字符串长度参考值，因此函数对象比普通函数更加灵活。
    假设我们有一串数字，要从中找出一个不小于10的数字，可以定义如下相应的类
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Upper
{
public:
    Upper(int min = 0):m_min(min) {}
    bool operator()(int value) const {
        return value >= m_min;
    }
private:
    int m_min;
};

class B{
public:
    B(int n=0) : th(n),count(1) {
        
    }
    bool operator()(int) {
        cout << "count "<<count << endl;
        return count++ == th;
    }
    int getCount() const{
        return count;
    }
private:
    int th;
    int count;
};

int main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(10);
    vec.push_back(15);
    vector<int>::iterator iter = find_if(vec.begin(),vec.end(),Upper(10));
    cout << *iter << std::endl;

    B b(3);
    vector<int>::iterator it = find_if(vec.begin(),vec.end(),b);
    cout << *it << endl;
    cout << b.getCount() << endl;
}
 
