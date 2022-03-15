#include <iostream>
#include <thread>

using namespace std;
int N=500;
constexpr int T=25;
void func1()
{
	for(auto i=0;i<N;++i)
	{
		cout<<"func1 called:"<<i<<"\n";
		this_thread::sleep_for(25ms);
	}
}
void func2()
{
	for(auto i=0;i<N;++i)
	{
		cout<<"func2 called:"<<i<<"\n";
		this_thread::sleep_for(25ms);
	}
}
void func3()
{
	for(auto i=0;i<N;++i)
	{
		cout<<"func3 called:"<<i<<"\n";
		this_thread::sleep_for(25ms);
	}
}

int main()
{
	//thread_id t1,t2,t3;
	thread t1(func1);
	thread t2(func2);
	thread t3(func3);
	t3.join();
	t2.join();
	t1.join();
	return 0;
}
