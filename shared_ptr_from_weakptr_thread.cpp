#include <iostream>
#include <functional>
#include <memory>
#include <atomic>
#include <thread>

int main() {

 auto sp = std::shared_ptr<std::atomic_int>(new std::atomic_int());

 //Reader
 //A weak_ptr is created and captured (syntax requires requires c++14).
 std::thread r([wp = std::weak_ptr<std::atomic_int>(sp)]() { //weak_ptr created. ref count: 1, weak count: 1
  while(true) {
   //Acquire a shared_ptr through lock() 
   if(auto p = wp.lock()) {
    //shared_ptr acquired. ref count is 1 or 2
    std::cout << *p << "\n";
   } else {
    //shared_ptr could not be acquired. ref count 0
    break;
   }
   //sleep
   std::this_thread::sleep_for(std::chrono::seconds(1));
  }
 });

 //Writer
 //The shared_ptr is moved and captured so the ref count stays 1
 //If the shared_ptr is copied instead of moved, this program will never 
 //     end because the reader would never exit (try that!).
 //Move in capture clause requires c++14
 std::thread w([mp = std::move(sp)]() { //shared_ptr moved. ref count: 1
  for(int i=1; i<=5; i++) {
   *mp = i; //change managed object
   std::this_thread::sleep_for(std::chrono::seconds(1));
  }
 });

 //Join the threads.
 w.join();
 r.join();
 return 0;
}
