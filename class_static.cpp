#include <iostream>
#include <thread>
#include <cstdio>
#include <chrono>

using namespace std;
using std::ref;

class A
{
	private:
		int i;
		//thread_local i;
	public:
		A():i{0}
		{
			++i;
			printf("ctor called:%d %p\n",i,this);
		}
		~A()
		{
			printf("dtor called:%d %p\n",i,this);
		}
		void run()
		{
			++i;
			this_thread::sleep_for(100ms);
			printf("run called:%d %p\n",i,this);
		}
};


int main()
{
	int N=10;
	thread T[N];
	for(int i=0;i<N;++i)
	{
		A *a = new A;
		T[i]= thread(&A::run,a);
		delete a;
	}
	for(int i=0;i<N;++i)
		T[i].join();
	return 0;
}
