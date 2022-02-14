#include <memory>
#include <iostream>

auto f(std::unique_ptr<int> ptr) {
  *ptr = 42;
  return ptr;
}
auto f1(std::unique_ptr<int> &ptr) {
  *ptr = 43;
  //return ptr;
}

int main() {
  auto ptr = std::make_unique<int>();
  ptr = f(std::move(ptr));
  std::cout<<*ptr<<std::endl;
  std::unique_ptr<int> ptr1 = std::unique_ptr<int>(new int);
  //auto ptr1 = std::make_unique<int>();
  f1(ptr1);
  std::cout<<*ptr1<<std::endl;
}
