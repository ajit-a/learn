#include <memory>

auto f(std::auto_ptr<int> ptr) {
  *ptr = 42;
  return ptr;
}

int main() {
  auto ptr = std::auto_ptr<int>();
  ptr = f(ptr);
}
