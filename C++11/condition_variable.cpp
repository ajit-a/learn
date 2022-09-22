// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <unistd.h>

/*Similar implementation can be done using latch or barrier.
They wait for the number of threads to come provided in initialization
https://www.youtube.com/watch?v=ywJ4cq67-uc 55min*/
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id (int id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (!ready){ std::cout<<"id:"<<id<<" ready:"<<ready<<std::endl; cv.wait(lck);}
  //while (!ready) cv.wait(lck);
  //cv.wait(lck);
  // ...
  std::cout << "thread " << id << '\n';
  sleep(2);
}

void go() {
  //std::unique_lock<std::mutex> lck(mtx);
  std::lock_guard<std::mutex> somelck(mtx);
  ready = true;
  cv.notify_all();
  sleep(10);
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_id,i);

  std::cout << "10 threads ready to race...\n";
  go();                       // go!

  for (auto& th : threads) th.join();

  return 0;
}
