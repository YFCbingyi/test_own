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
};

// function that calls the delete [] on received pointer
void deleter(Sample * x) {
	std::cout << "DELETER FUNCTION CALLED\n";
	delete[] x;
}

void smart_p_int(void) {
	std::cout<<"\n\n******* int ********* "<<std::endl;

	// Creating a shared_ptr through make_shared
	std::shared_ptr<int> p1 = std::make_shared<int>();
	*p1 = 78;
	std::cout << "p1 value = " << *p1 << std::endl;
	std::cout << "p1 = " <<  p1 << std::endl;
	std::cout << "p1.use_count = " <<  p1.use_count() << std::endl;
 
	// Second shared_ptr object will also point to same pointer internally
	// It will make the reference count to 2.
	std::shared_ptr<int> p2(p1);
 
	// Shows the reference count
	std::cout << "After create new smart pointer: " << std::endl;
	
	// Comparing smart pointers
	if (p1 == p2) {
		std::cout << "  p1 and p2 are pointing to same pointer\n";
	}
 
	std::cout<<"Reset p1 "<<std::endl;
	// Reset the shared_ptr, in this case it will not point to any Pointer internally
	// hence its reference count will become 0.
	p1.reset();

	// Shows the reference count
	std::cout << "  p1 Reference count = " << p1.use_count() << std::endl;
	std::cout << "  p1 = " <<  p1 << std::endl;
	std::cout << "  p2 Reference count = " << p2.use_count() << std::endl;
	std::cout << "  p2 = " <<  p2 << std::endl;
 
	// Reset the shared_ptr, in this case it will point to a new Pointer internally
	// hence its reference count will become 1.
 
	p1.reset(new int(11));
    std::cout<<"Reset p1 to new object"<<std::endl;
	std::cout << "  p1  Reference Count = " << p1.use_count() << std::endl;
    std::cout << "  p1 = " <<  p1 << std::endl;
	// Assigning nullptr will de-attach the associated pointer and make it to point null
	p1 = nullptr;
 
	std::cout << "  p1  Reference Count = " << p1.use_count() << std::endl;
 
	if (!p1) {
		std::cout << "p1 is NULL" << std::endl;
	}
}

void smart_p_sample(void) {
	std::cout<<"\n\n******* Sample ********* "<<std::endl;

	// Creating a shared_ptr through make_shared
	std::shared_ptr<Sample> p1 = std::make_shared<Sample>();
	std::cout << "p1 = " <<  p1 << std::endl;
	std::cout << "p1.use_count = " <<  p1.use_count() << std::endl;
 
	// Second shared_ptr object will also point to same pointer internally
	// It will make the reference count to 2.
	std::shared_ptr<Sample> p2(p1);
 
	// Shows the reference count
	std::cout << "After create new smart pointer: " << std::endl;
	
	
 
	// Comparing smart pointers
	if (p1 == p2) {
		std::cout << "  p1 and p2 are pointing to same pointer\n";
	}
 
	std::cout<<"Reset p1 "<<std::endl;
	// Reset the shared_ptr, in this case it will not point to any Pointer internally
	// hence its reference count will become 0.
	p1.reset();

	// Shows the reference count
	std::cout << "  p1 Reference count = " << p1.use_count() << std::endl;
	std::cout << "  p1 = " <<  p1 << std::endl;
	std::cout << "  p2 Reference count = " << p2.use_count() << std::endl;
	std::cout << "  p2 = " <<  p2 << std::endl;
 
	// Reset the shared_ptr, in this case it will point to a new Pointer internally
	// hence its reference count will become 1.
 
	p1.reset(new Sample());
    std::cout<<"Reset p1 to new object"<<std::endl;
	std::cout << "  p1  Reference Count = " << p1.use_count() << std::endl;
    std::cout << "  p1 = " <<  p1 << std::endl;
	// Assigning nullptr will de-attach the associated pointer and make it to point null
	p1 = nullptr;
 
	std::cout << "  p1  Reference Count = " << p1.use_count() << std::endl;
 
	if (!p1) {
		std::cout << "  p1 is NULL" << std::endl;
	}

	// More
	std::cout<<"Assign p2 to p1 "<<std::endl;
	p1 = p2;
	// Shows the reference count
	std::cout << "  p1 Reference count = " << p1.use_count() << std::endl;
	std::cout << "  p1 = " <<  p1 << std::endl;
	std::cout << "  p2 Reference count = " << p2.use_count() << std::endl;
	std::cout << "  p2 = " <<  p2 << std::endl;
}

void smart_p_sample_init(void) {
	std::cout<<"\n\n******* Sample Init ********* "<<std::endl;

	// Creating a shared_ptr through make_shared
	std::shared_ptr<Sample> p1;
	std::cout << "p1 = " <<  p1 << std::endl;
	std::cout << "p1.use_count = " <<  p1.use_count() << std::endl;


	std::shared_ptr<Sample> p2(new Sample());
	std::cout << "p2 = " <<  p2 << std::endl;
	std::cout << "p2.use_count = " <<  p2.use_count() << std::endl;

	// 错误的初始化方式
	//std::shared_ptr<Sample> p3  = new Sample();
}

int main() {

	smart_p_int();
	smart_p_sample();

	smart_p_sample_init();

	std::cout<<"\n\n******* Sample Array ********* "<<std::endl;
	// 注意：一定需要传入delte函数的，否则使用缺省的delete函数会出错的
	//std::shared_ptr<Sample> p3(new Sample[3]);
	std::shared_ptr<Sample> p4(new Sample[3], deleter);

	return 0;
}
