#include <functional>
#include <iostream>
 
class A {

public:
};

int _test( class A a) { return 0;}


void Test(A a) {
  _test(a);

  // 对 _test(a); 而言，这里的a为左值，因为这里的a对调用方而言是具名的，_test内部对a也是可以进行 &取址操作的。
  // 但这个a在调用完毕后很快被销毁，毕竟它只是一个临时变量。
}

class AB {
public:
  AB() :array(new int[3]{1, 2, 3}) {

  }
  ~AB() {
    if(nullptr != array) {
      delete [] array;
    }
  }
  
  AB( AB& a) {
    array = a.array;
    a.array = nullptr;
    std::cout << "Copy Construct" << std::endl;
  }
//  private:
    int *array{nullptr};
};

int main() {
    A a; // a为左值，因为其有明确名字，且对a进行 &a 是合法的。

    Test(A());  // A() 为右值，因为A()产生一个临时对象，临时对象没有名字且无法进行 &取址操作。


    AB a1;
    std::cout << "a1 = " << a1.array << std::endl;
    AB a2(a1);
    std::cout << "a2 = " << a2.array << std::endl;
}
