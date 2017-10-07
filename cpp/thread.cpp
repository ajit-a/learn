#include <iostream>
#include <thread>
using namespace std;
void print()
{
	cout<<"Thread called\n";
	cout<<"Thread concurrency "<<thread::hardware_concurrency()<<endl;
}
int main()
{
	thread t(&print);
	t.join();
	return 0;
}
