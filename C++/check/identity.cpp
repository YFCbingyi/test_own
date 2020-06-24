/*************************************************************************
	> File Name: identity.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月08日 星期一 10时54分03秒
 ************************************************************************/

#include<iostream>
#include<cmath>
using namespace std;

bool check(const std::string &id) {
    int weight[] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    char validata[] = {'1','0','X','9','8','7','6','5','4','3','2'};

    if(id.length() == 18) {
        int sum = 0;
        for(int i = 0; i < 17; i++) {
            cout << weight[i] << " * " << (id[i] - '0') << " = " <<(id[i] - '0') * weight[i] << endl;
            sum = sum + (id[i] - '0') * weight[i];
        }
        cout << sum << endl;
        int mode = sum%11;
        cout << mode << endl;
        if(validata[mode] == id[17])
            return true;
    }
    return false;
}

int main() {
    
    string id = "142202199503252865";
    if(check(id)) {
        cout << " true " << endl;
    } else {
        cout << " false " << endl;
    }
}
