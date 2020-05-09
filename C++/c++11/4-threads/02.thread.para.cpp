#include <iostream>
#include <thread>
#include <string.h>

void Hello(char* what) {

	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Hello, " << what << "!" << std::endl;
	printf("[In Thread]Addr for tmpStr = %p\n", what);


	strcpy(what, "Thread World.");
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
	char tmpStr[32] = "New World";
	printf("Addr for tmpStr = %p\n", tmpStr);
	
	printf("%p, %p\n", Hello, &Hello);	// Same
	std::thread th(Hello, tmpStr);

	th.join();

	printf("%s\n", tmpStr);
	// 等价于使用 bind：
	//   std::thread th(std::bind(&Hello, "World"));

	return 0;
}


/*

征服C指针》中有特别说明：
为了照顾在表达式中的函数名可以解读成“指向函数的指针”这一规则，ANSI C有如下规定：
   表达式中的函数自动转换成“指向函数的指针”。

取址运算符&和sizeof运算符时例外。（函数的sizeof一般无法计算）

函数调用运算符()的操作数不是“函数”，而是“函数指针”。因此，(****demofunc)(1, 2)也能顺利运行。每次解引用都会变函数，但是因为在表达式中就瞬间变指针。




型（这也是 C 语言需要头文件的原因）。所以，在设计函数作为函数参数而需要类型时遇到了问题。C 语言本质上是高级汇编，而函数在汇编里本质上就是代码段（code segment）的一个起址，所以很自然就想出了函数指针这种类型。这是一种纯粹拍脑袋的、想当然的糟糕设计，因为函数指针这种类型根本没法解引（因为没有函数类型没法接，所以函数指针干脆被设计成解引后还是原函数指针），所以在 C 语言中才会出现像下面这样啼笑皆非的函数指针的使用：
myfunction f3 = &func;
f3(1, 2);
(**f3)(1, 2);
(**********f3)(1, 2);


typedef int (*myfunction)(int a, int b);
myfunction f = &func;


typedef std::function<int(int, int)> myfunction;
myfunction f(func);


*/