#include <iostream>
using namespace std;
void func()
{
	static int i=10;
	cout<<i<<endl;
	i=11;
}

int main()
{
	func();
	func();
	return 0;
}
