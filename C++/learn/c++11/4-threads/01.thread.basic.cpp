#include <iostream>
#include <thread>

void hello() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Hello, World!" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
  // 创建一个线程对象，注意函数 Hello 将立即运行。
  std::thread th(&hello);

  // 等待线程结束。
  th.join();

  return 0;
}
