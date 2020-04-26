#include <iostream>
#include <thread>


// By default all arguments are copied into the internal storage of new thread.
void threadCallback0(int const & x)
{
    int & y = const_cast<int &>(x);
    y++;
    std::cout<< "Inside Thread x = " << x<< std::endl;
}

void threadCallback1(int  *x)
{
    *x = *x + 1;
    std::cout<<"Inside Thread x = "<< *x << std::endl;
}

int main()
{
    int x = 9;
    std::cout<<"In Main Thread : Before Thread Start x = "<<x<<std::endl;
    // It is useless even define x is reference type
    std::thread threadObj1(threadCallback0, x);
    threadObj1.join();
    std::cout<<"In Main Thread : After Thread Joins x = "<<x<<std::endl;

	// MUST do it as follow
    std::cout<<"\n\nIn Main Thread : Before Thread Start x = "<<x<<std::endl;
    std::thread threadObj2(threadCallback0, std::ref(x));
    threadObj2.join();
    std::cout<<"In Main Thread : After Thread Joins x = "<<x<<std::endl;


    std::cout<<"\n\nIn Main Thread : Before Thread Start x = "<<x<<std::endl;
    std::thread threadObj3(threadCallback1, &x);
    threadObj3.join();
    std::cout<<"In Main Thread : After Thread Joins x = "<<x<<std::endl;

    return 0;
}
