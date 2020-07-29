#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


std::mutex g_mutex;
int g_count = 0;

void Counter() {
  g_mutex.lock();

  int i = ++g_count;
  std::cout << std::this_thread::get_id() << "  count: " << i << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));

  // 前面代码如有异常，unlock 就调不到了。
  g_mutex.unlock();
}

int main() {
  const std::size_t SIZE = 4;

  // 创建一组线程。
  std::vector<std::thread> v;
  v.reserve(SIZE);

  for (std::size_t i = 0; i < SIZE; ++i) {
    v.emplace_back(&Counter);
  }

  // 等待所有线程结束。
  for (std::thread& t : v) {
    t.join();
  }

  return 0;
}

