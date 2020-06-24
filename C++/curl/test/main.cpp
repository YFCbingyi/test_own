/*************************************************************************
	> File Name: main.cpp
	> Author: chenbingyi
	> Mail: chenbingyi@riseauto.cn
	> Created Time: 2020年06月24日 星期三 10时29分50秒
 ************************************************************************/

#include<iostream>
#include "IHtml.h"
using namespace std;

int main() {

	std::string url = "www.wasag.csa.com";
	std::string result;

	IHtml::getHtmlData(url,result);

	cout << "result "<< result << endl;

	return 0;
}

