#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex M;
std::condition_variable CV;
int var = 0;


int main()
{
    std::thread t1{
        []{
            std::unique_lock<std::mutex> lck{M};
            while(var != 1){
                CV.wait(lck);
                std::cout << "t1 woken up and (i != 1) = " 
                          << (var != 1) << std::endl;
            }
						std::cout<<"Processing:"<<var<<std::endl;
        }
    };

    std::thread t2{
        []{
            std::unique_lock<std::mutex> lck{M};
            while(var != 2){
                CV.wait(lck);
                std::cout << "t2 woken up and (i != 2) = " 
                          << (var != 2) << std::endl;
            }
						std::cout<<"Processing:"<<var<<std::endl;
        }
    };

    std::thread t3{
        []{
            std::unique_lock<std::mutex> lck{M};
            while(var != 3){
                CV.wait(lck);
                std::cout << "t3 woken up and (i != 3) = " 
                          << (var != 3) << std::endl;
            }
						std::cout<<"Processing:"<<var<<std::endl;
        }
    };

    std::thread t4{
        []{
            std::unique_lock<std::mutex> lck{M};
            while(var != 4){
                CV.wait(lck);
                std::cout << "t4 woken up and (i != 4) = " 
                          << (var != 4) << std::endl;
            }
						std::cout<<"Processing:"<<var<<std::endl;
        }
    };

    for(int i = 0; i < 6; ++i){
        std::unique_lock<std::mutex> lck{M};
        var = i;
        CV.notify_all();
        lck.unlock();
        std::this_thread::sleep_for(std::chrono::seconds{1});
        std::cout << "\n\n";
    }

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}  
