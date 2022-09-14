#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

class threadpool
{
  private:
    std::condition_variable cv{};
    std::mutex mtx{};
    std::vector<std::thread> threads;
    std::queue<int*> _queue{};
  public:
    void process(int *d)
    {
      std::lock_guard<std::mutex> lock{mtx};
      _queue.push(d);
      cv.notify_all();  
    }
    void workerThread()
    {
       std::unique_lock<std::mutex> lock{mtx};
       while(true)
       {
        cv.wait(lock,[this](){return !_queue.empty();});
        auto d=_queue.front();
        _queue.pop();
        std::cout<<*d<<" Processed by thread:"<<std::this_thread::get_id()<<std::endl;
        delete d;
       }
    }

    /*Not a good idea to create threads in ctor as object might not have been initialized properly and cause seg fault*/
    threadpool():cv{},mtx{},threads{},_queue{}
    {
      threads.reserve(5);
      for(int i=0;i<5;++i)
      {
				//All 3 lines below work
        //threads[i] = std::thread(&threadpool::workerThread,this);
        threads.emplace_back(&threadpool::workerThread,this);
        //threads[i] = std::move(std::thread(&threadpool::workerThread,this));
      }
    }
    ~threadpool()
    {
      for(auto& tid:threads)
				tid.join();
    }

};

int * getdata()
{
  int val;
  std::cin>>val;
  int *a = new int(val);
  return a;
}
int main()
{
  threadpool tp;
  while (int *d = getdata())
  {
    tp.process(d);
  }
}
