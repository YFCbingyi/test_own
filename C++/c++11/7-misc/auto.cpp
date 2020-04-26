// auto is introduces in C++11. With auto we can declare a variable without specifying its type. Its type will be deduced by the data to which its initializing.

/*
// Storing a int inside a auto variable
auto var_1 = 5;
 
// Storing a character inside a auto variable
auto var_2 = 'C';
 
std::cout<<var_1<<std::endl;
std::cout<<var_2<<std::endl;



*/

#include <iostream>
#include <typeinfo>
#include <map>
#include <string>
#include <iterator>
 
auto sum(int x, int y) -> int	// C++11
//auto sum(int x, int y)			// C++14
{
	return x + y;
}
 
int main()
{
 
	// Storing a int inside a auto variable
	auto var_1 = 5;
 
	// Storing a character inside a auto variable
	auto var_2 = 'C';

 
	std::cout << var_1 << std::endl;
	std::cout << var_2 << std::endl;
 
	// Storing Lambda function inside a auto variable
	auto fun_sum = [](int a , int b)
	{
		return a+b;
	};
 
	std::cout << fun_sum(4, 5) << std::endl;
 
	std::map<std::string, std::string> mapOfStrs;
 
	// Insert data in Map
	mapOfStrs.insert(std::pair<std::string, std::string>("first", "1"));
	mapOfStrs.insert(std::pair<std::string, std::string>("sec", "2"));
	mapOfStrs.insert(std::pair<std::string, std::string>("thirs", "3"));
 
	// Iterate over the map and display all data;
	// Create an iterator
	std::map<std::string, std::string>::iterator it = mapOfStrs.begin();
	while (it != mapOfStrs.end())
	{
		std::cout << it->first << "::" << it->second << std::endl;
		it++;
	}
 
	// Iterate using auto
	auto itr = mapOfStrs.begin();
	while (itr != mapOfStrs.end())
	{
		std::cout << itr->first << "::" << itr->second << std::endl;
		itr++;
	}
 
	auto x = 1;
	// Cannot change the type of already initialized auto variable
	// Error will occur at compile time
	// x = "dummy";
 
	// Can not declare auto variable without initialization
	// because its type is based on initiazing value.
	//auto a;
 
	auto value = sum(3, 5);
 
	std::cout << value << std::endl;
	return 0;
}
