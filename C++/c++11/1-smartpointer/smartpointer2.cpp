// std::shared_ptr<int> p1(new int());
//  p1.use_count();
// std::shared_ptr<int> p1 = std::make_shared<int>();
// Error: std::shared_ptr<int> p1 = new int(); // Compile error

//  p1.reset(); - It decrease its reference count by 1 and if reference count becomes 0 then it deleted the pointer

#include <iostream>
#include <memory> // We need to include this for shared_ptr
 
 struct Sample {
	Sample() {
		std::cout << "SAMPLE constructor\n";
	}
	~Sample() {
		std::cout << "SAMPLE destructor\n";
	}

	int number;
};

// function that calls the delete [] on received pointer
void deleter(Sample * x) {
	std::cout << "DELETER FUNCTION CALLED\n";
	delete[] x;
}

void smart_p_sample(void) {
	std::cout<<"\n\n******* Sample ********* "<<std::endl;

	// Creating a shared_ptr through make_shared
	std::shared_ptr<Sample> p1(new Sample());
	std::cout << "p1 = " <<  p1 << std::endl;
	std::cout << "p1 = " <<  p1.get() << std::endl;
	std::cout << "p1.use_count = " <<  p1.use_count() << std::endl;

	//  注意，此处两者的地址一样，但是是两类不同的数据类型
	if(p1) {
		std::cout << "p1 NOT null : " << p1->number << std::endl;
	}

	p1->number = 199;
	std::cout << "number for p1 " << (*p1).number << std::endl;

	p1.reset();
	if(p1) {
		std::cout << "p1 NOT null " << std::endl;
	}
	else
	{
		std::cout << "p1 is null " << std::endl;
	}
	
	std::cout << "p1 = " <<p1.get() << std::endl;

}

int main()
{
	smart_p_sample();
	return 0;
}
