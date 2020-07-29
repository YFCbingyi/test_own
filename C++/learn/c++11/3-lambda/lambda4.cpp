#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class OddCounter1
{
	// tracks the count of odd numbers encountered
	int mCounter = 0;

public:
	int getCount()
	{
		return mCounter;
	}
	void update(std::vector<int> & vec)
	{
		// Capturing member variable by value will not work
        // Will result in Compile Error
// 		std::for_each(vec.begin(), vec.end(), [mCounter](int element){
// 			if(element % 2)
// 				mCounter++; // Accessing member variable from outer scope
// 		});
	}
};
 
class OddCounter2
{
	// tracks the count of odd numbers encountered
	int mCounter = 0;

public:
	int getCount()
	{
		return mCounter;
	}
	void update(std::vector<int> & vec)
	{
		// Traverse the vector and increment mCounter if element is odd
		// this is captured by value inside lambda
		std::for_each(vec.begin(), vec.end(), [this](int element){
			if(element % 2)
				mCounter++; // Accessing member variable from outer scope
		});
	}
};
 
 
int main(int argc, char **argv)
{
	std::vector<int> vec = {12,3,2,1,8,9,0,2,3,9,7};
 
	OddCounter2 counterObj;
 
	//Passing the vector to OddCounter object
	counterObj.update(vec);
 
	int count = counterObj.getCount();
 
	std::cout<<"Counter = "<<count<<std::endl;
	return 0;
}
