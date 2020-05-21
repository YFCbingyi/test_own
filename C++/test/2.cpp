/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年05月19日 星期二 18时10分45秒
 ************************************************************************/

#include<iostream>
#include <string>

using namespace std;


int main(int argc,char **argv) {

    for(int size = 0; size < 200; size++) {
        int n = (size/50 == 0) ? 1 : (size/50);
        std::cout << "n = "<<n << std::endl;
    } 

    return 0;
}
