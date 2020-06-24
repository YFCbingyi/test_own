/*************************************************************************
	> File Name: mobilephone.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月08日 星期一 11时06分46秒
 ************************************************************************/

#include<iostream>
#include<regex>
using namespace std;

/*
 * 目前三大运营商的手机号段分布如下：

中国电信号段133、153、173、177、180、181、189、191、193、199

中国联通号段130、131、132、155、156、166、175、176、185、186、166

中国移动号段134(0-8)、135、136、137、138、139、147、150、151、152、157、158、159、172、178、182、183、184、187、188、198
* */

bool check(const std::string &phone) {
    regex e("^1((3[0-9])|(4[0-9])|(7[0-9])|(5([0-3]|[5-9]))|(8(0|2|[5-9])))\\d{8}$");
    //regex e("^1\\d{8}$");
    if(regex_match(phone,e)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    string num = "15611769175";
    if(check(num)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}

