#include <iostream>
#include <thread>
#include <utility>
#include <vector>
#include <map>

template<class T, class U>
auto add(T t, U u) { return t + u; } // the return type is the type of operator+(T, U)


void bar(std::shared_ptr<int> p) {}

class FOO { };

void foo(int* p) {}
// Can guess return type: but int -> float
auto foo(int i) {
  if ( i < 0 )
    return -1;
  else
    //return 2.0
	return 2;
}

int main() {
	auto i = 42;        // i is an int
	auto l = 42LL;      // l is an long long
	auto p = new FOO(); // p is a FOO*


	int* p1 = NULL;
	int* p2 = nullptr;   
	if(p1 == p2) {
		printf("EQ!\n");
	}

	foo(nullptr);
	bar(nullptr);


	bool f = nullptr;		// warn
	//int ks = nullptr;		// Error

	auto a = 1 + 2;            // type of a is int
    auto b = add(1, 1.2);      // type of b is double


	std::map<std::string, std::vector<int>> map;
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	map["one"] = v;

	for(const auto& kvp : map)  {
		std::cout << kvp.first << std::endl;

		for(auto v : kvp.second) {
			std::cout << v << std::endl;
		}
	}

	return 0;
}
