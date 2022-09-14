#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <iomanip>
#include <unistd.h>

using namespace std;

#include <atomic>
class Spinlock
{
private:
    std::atomic_flag atomic_flag = ATOMIC_FLAG_INIT;
public:
    void lock()
    {
       while (atomic_flag.test_and_set(std::memory_order_acquire))
        {
        }
  
    }
    void unlock()
    {
        atomic_flag.clear(std::memory_order_release);
    }
};
const int count_to = 10000;
//const int count_to = 1000000;

volatile int value = 0;

Spinlock l;

int task(int count_to)
{

    std::cout << "Started  " << this_thread::get_id() << std::endl;
    for (int i = 0; i < count_to; ++i)
    {
        l.lock();
        value++;
        usleep(1);
        l.unlock();
    }

    return 0;
}

int main(int, char **)
{
    time_t begin, end; // time_t is a datatype to store time values.
    time(&begin);      // note time before execution
    const int num_workers = 5;
    std::vector<std::thread> threads;
    std::cout << "SpinLock inc MyTest start" << std::endl;
    value = 0;
    for (int i = 0; i < num_workers; ++i)
        threads.push_back(std::move(std::thread(task, count_to)));

    for (auto it = threads.begin(); it != threads.end(); it++)
        it->join();
    time(&end); // note time after execution
    double difference = difftime(end, begin);
    std::cout << "job done" << std::endl;
    std::cout << "count_: " << value << std::endl;
    std::cout << "time taken for function() %.2lf seconds.\n"
              << std::endl;

    std::cout << std::fixed << std::setw(11) << std::setprecision(6)
              << std::setfill('0') << difference <<endl;
    if (value == count_to * num_workers)
    {
        std::cout << "SpinLock  passed" << std::endl;
        return true;
    }
    else
    {
        std::cout << "SpinLock failed" << std::endl;
        return false;
    }
}

