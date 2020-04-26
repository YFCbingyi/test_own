#include <iostream>
#include <thread>
 
void thread_function()
{
    for(int i = 0; i < 10; i++)
    	std::cout << "  [" << i << "]  thread function Executing: ID  = " <<std::this_thread::get_id()<<std::endl;  
}
 
class DisplayThread
{
public:
    void operator()()     
    {
        for(int i = 0; i < 10; i++)
        	std::cout << "  [" << i << "]  Display Thread Executing"<<std::endl;
    }
};
 

class DummyClass {
public:
    DummyClass()
    {}
    DummyClass(const DummyClass & obj)
    {}
    void sampleMemberFunction(int x)
    {
        std::cout<<"Inside sampleMemberFunction "<<x<<std::endl;
    }
};

int main()  
{
    // Function Pointer
    std::thread threadObj1(thread_function);
    for(int i = 0; i < 10; i++)
    	std::cout << "  [" << i << "]Display From MainThread"<<std::endl;

    threadObj1.join();
    
    if(threadObj1.joinable())
    	threadObj1.join();   // If there NO 'if', terminating with uncaught exception of type std::__1::system_error: thread::join failed
    std::cout<<"Exit of Main function"<<std::endl;
    
    // Function Objects
    std::thread threadObj2( (DisplayThread()) );
    for(int i = 0; i < 10; i++)
        std::cout << "  [" << i << "]Display From MainThread"<<std::endl;

    std::cout<<"Waiting For Thread to complete"<<std::endl;
    
    if(threadObj2.joinable())
    	threadObj2.join();
    std::cout<<"Exit of Main function"<<std::endl;

    
    // Lambda functions
    std::thread threadObj3([]{
            for(int i = 0; i < 10; i++)
                std::cout<<"Display Thread Executing"<<std::endl;
            });
            
    for(int i = 0; i < 10; i++)
        std::cout << "  [" << i << "]Display From MainThread"<<std::endl;
        
    threadObj3.join();
    std::cout<<"Exiting from Main Thread"<<std::endl;
    
    
    // member function of a class
    DummyClass dummyObj;
    int x = 10;
    std::thread threadObj4(&DummyClass::sampleMemberFunction, &dummyObj, x);
    threadObj4.join();
    
    
    return 0;
}
