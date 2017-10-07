#include <memory>

auto f(std::unique_ptr<int> ptr) {
  *ptr = 42;
  return ptr;
}

int main() {
  auto ptr = std::make_unique<int>();
  ptr = f(ptr);
  //ptr = f(std::move(ptr));
}
