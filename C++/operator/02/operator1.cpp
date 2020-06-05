/*************************************************************************
	> File Name: operator1.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月03日 星期三 18时02分50秒
 ************************************************************************/

#include<iostream>
#include<set>
using namespace std;

class Sort{
public:
    bool operator()(const string &str1,const string &str2) const {
        cout << str1 <<" compare "<< str2 << endl;
        return str1 > str2;
    }
};

int main() {
    set<string,Sort> myset;
    cout << "A "<<std::endl;
    myset.insert("A");
    cout << "C" << endl;
    myset.insert("C");
    cout << "E" << endl;
    myset.insert("E");
    cout << "X" << endl;
    myset.insert("X");
    cout << "B" << endl;
    myset.insert("B");
    cout << "D" << endl;
    myset.insert("D");
    
    set<string,Sort>::iterator it;
    for(it = myset.begin();it != myset.end(); ++it) {
        cout << *it << std::endl;
    }
}
