/*************************************************************************
	> File Name: identity.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月08日 星期一 10时54分03秒
 ************************************************************************/

#include<iostream>
#include<cmath>
#include<regex>
using namespace std;

bool check_provinceId(const std::string &id);
/*
*检查身份证第18位*/
bool check(const std::string &id) {
    int weight[] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    char validata[] = {'1','0','X','9','8','7','6','5','4','3','2'};

    if(id.length() == 18) {
        if(!check_provinceId(id))
            return false;
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
    } else 
        cout << "length is not 18" << endl;
    return false;
}

static char provinceIds[36] = {11,12,13,14,15,
                           21,22,23,31,32,
                           33,34,35,36,37,
                           41,42,43,44,45,
                           46,51,52,53,54,
                           61,62,63,64,65,
                           66,71,81,82,91};

/*
* 检查身份证地址码*/
bool check_provinceId(const std::string &id) {
    regex e("^((1[1-5])|(2[1-3])|(3[1-7])|(4[1-6])|(5[1-4])|(6[1-6])|(71)|(8[1-2])|(91))[0-9]{8}(0[1-9]|1[0-2])(0[1-9]|1[0-9]|2[0-9]|3[0-1])[0-9]{4}$");
    if(regex_match(id,e))
        return true;
    else
        return false;
}

int main() {
    
    string id = "712202199511010618";
    if(check(id)) {
        cout << " true " << endl;
    } else {
        cout << " false " << endl;
    }
}
