#include <iostream>
#include <string>
 

// 特别注意不能用lambda函数访问已经返回的函数中的局部变量。
int main(int argc, char **argv)
{
	std::string msg = "Hello";
	int counter = 10;
	int noWay = 100;
 
	// Defining Lambda function and
	// Capturing Local variables by [[value]]
	// 添加了一个mutable 修饰，则这些变量可以被修改，但是不能反应到outter scope中
	auto func = [=]  () mutable {
		std::cout<<"Inside Lambda :: msg = "<<msg<<std::endl;
		std::cout<<"Inside Lambda :: counter = "<<counter<<std::endl;
 
		// Change the counter & msg
		// Change will not affect the outer variable because counter variable is
		// captured by value in Lambda function
		msg = "Temp";
		counter = 20;
 
		std::cout<<"Inside Lambda :: After changing :: msg = "<<msg<<std::endl;
		std::cout<<"Inside Lambda :: After changing :: counter = "<<counter<<std::endl;
 
 		//std::cout<<"Inside Lambda :: After changing :: counter = "<<noWay<<std::endl;
		};
 
	//Call the Lambda function
	func();
 
	//Values of local variables are not changed.
	std::cout<<"msg = "<<msg<<std::endl;
	std::cout<<"counter = "<<counter<<std::endl;
 
 	// Defining Lambda function and
	// Capturing Local variables by Reference
	auto func1 = [&msg, &counter]  () {
		std::cout<<"Inside Lambda :: msg = "<<msg<<std::endl;
		std::cout<<"Inside Lambda :: counter = "<<counter<<std::endl;
 
		// Change the counter & msg
		// Change will affect the outer variable because counter variable is
		// captured by Reference in Lambda function
		msg = "Temp";
		counter = 20;
 
		std::cout<<"Inside Lambda :: After changing :: msg = "<<msg<<std::endl;
		std::cout<<"Inside Lambda :: After changing :: counter = "<<counter<<std::endl;
 
	};

 
	//Call the Lambda function
	func1();
 
	//Values of local variables are not changed.
	std::cout<<"msg = "<<msg<<std::endl;
	std::cout<<"counter = "<<counter<<std::endl;
	

#if 0
	auto func2 = [msg, counter]  ()  {
		std::cout<<"Inside Lambda :: msg = "<<msg<<std::endl;
		std::cout<<"Inside Lambda :: counter = "<<counter<<std::endl;
 
		// Change the counter & msg
		// Change will not affect the outer variable because counter variable is
		// captured by value in Lambda function
		msg = "Temp";
		counter = 20;
 
		std::cout<<"Inside Lambda :: After changing :: msg = "<<msg<<std::endl;
		std::cout<<"Inside Lambda :: After changing :: counter = "<<counter<<std::endl;
 
 		//std::cout<<"Inside Lambda :: After changing :: counter = "<<noWay<<std::endl;
		};
#endif

	return 0;
}
