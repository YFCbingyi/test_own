//To do a simple thing we used a condition variable, a mutex and a pointer i.e. 3 items to catch a returned value.

// New method is future, promise
#include <iostream>
#include <thread>
#include <future>

void initiazer(std::promise<int> * promObj, int *money)
{
    std::cout<<"Inside Thread"<<std::endl;
    *money = 1000;
    promObj->set_value(35);
}
 
int main()
{
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();

    int money = 0;
    std::thread th(initiazer, &promiseObj, &money);

    std::cout<<futureObj.get()<<std::endl;
    std::cout << money << std::endl;
    th.join();
    return 0;
}

//If std::promise object is destroyed before setting the value the calling get() function on associated std::future object will throw exception