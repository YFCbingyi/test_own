#include <iostream>
#include <thread>

class Hello {
public:
  void operator()(const char* what) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Hello, " << what << "!" << std::endl;
  }
};

int main() {
  Hello hello;

  // 方式一：拷贝函数对象。
  std::thread t1(hello, "World");
  t1.join();

  // 方式二：不拷贝函数对象，通过 std::ref 传入引用。
  // 用户必须保证被线程引用的函数对象，拥有超出线程的生命期。 
  std::thread t2(std::ref(hello), "World");
  t2.join();

  return 0;
}
