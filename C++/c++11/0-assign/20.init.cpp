#include <iostream>
#include <vector>
#include <map>


// 此处可以演示arm汇编的例子
int fooi1(int idx) {

	int arr[4]{1, 2, 3, 9};
	return arr[idx] * 13;
}

int fooi2(int idx) {

	int arr[3] = {1, 2, 3};
	return arr[idx];
}


int foov1(int idx) {
	std::vector<int> iv = { 1, 2, 3};
	return iv[idx];
}

int main() {
	std::map<int, std::string> map1  {{1, "a"}, {2, "b"}};  
	std::string str = {"Hello World"}; 
}
