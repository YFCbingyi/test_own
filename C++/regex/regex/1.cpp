/*************************************************************************
	> File Name: 1.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月08日 星期一 11时16分13秒
 ************************************************************************/

#include<iostream>
#include<regex>
using namespace std;

int main() {
    cout << regex_match("123",regex("\\d")) << endl;
    cout << regex_match("123",regex("\\d+")) << endl;
    cout << regex_match("13711111111",regex("^((13[0-9])|(14[1]|[4-9])|(15([0-3]|[5-9]))|(16[2]|[5-7])|(17[0-3]|[5-8])|(18[0-9])|(19[1|8|9]))\\d{8}$")) << endl;
    cout << regex_match("13711111111",regex("^1((3[0-9])|(4[1]|[4-9])|(5([0-3]|[5-9]))|(6[2]|[5-7])|(7[0-3]|[5-8])|(8[0-9])|(9[1|8|9]))\\d{8}$")) << endl;
}
