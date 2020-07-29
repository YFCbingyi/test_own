#include <iostream>
#include <vector>
#include <map>

int main() {

	std::string str = "hello, world";  
	for(auto ch : str) {  
		std::cout << ch << std::endl;  
	} 

	std::vector<std::string> str_vec = {"i", "like",  "google"};  
	for(auto& it : str_vec) {  
		it = "c++";  
	}

	std::map<int, std::string> hash_map = {{1, "c++"}, {2, "java"}, {3, "python"}};  
	for(auto it : hash_map) {  
		std::cout << it.first << "\t" << it.second << std::endl;  
	} 

	std::map<std::string, std::vector<int>> map;
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	map["one"] = v;

	for(const auto &kvp : map)  {
		std::cout << kvp.first << std::endl;

		for(auto v : kvp.second) {
			std::cout << v << std::endl;
		}
	}
	std::cout << std::endl;

	int arr[] = {1,2,3,4,5};
	for(int &e : arr)  {
		e = e*e;
	}

	for(int &e : arr) {
		std::cout << e << std::endl;
	}

    std::cout << "Range-for over brace-init-list: \n";
 
    for (int x : {-1, -2, -3})
        std::cout << x << ' ';
    std::cout << '\n';

	return 0;
}