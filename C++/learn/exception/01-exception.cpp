/*************************************************************************
	> File Name: 01-exception.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年05月28日 星期四 09时52分04秒
 ************************************************************************/

#include <iostream>
#include <exception>
using namespace std;

double func_1(double a, double b)
{
	if (b == 0)
	{
		throw std::runtime_error("除数为0,算法错误");
	}
	return a / b;
}

int main()
{

	std::cout << " start " << std::endl;
	try
	{
		std::cout << func_1(2, 1) << std::endl;
		std::cout << func_1(1, 0) << std::endl;
		/* code */
	}
    catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << " over " << std::endl;

	return 0;
}
