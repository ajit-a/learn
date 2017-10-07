#include <memory>

auto f(std::shared_ptr<int> ptr) {
  *ptr = 42;
  return ptr;
}

int main() {
  auto ptr = std::make_shared<int>();
  ptr = f(ptr);
}
