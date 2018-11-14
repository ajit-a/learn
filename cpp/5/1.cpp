//http://www.gotw.ca/publications/mill17.htm
#include <iostream>

using namespace std;


template<typename T>
struct unary
{
	void operator()(const T &param)
	{
		cout<<"Template called"<<endl;
	}
};
template<>
struct unary<int>
{
	void operator()(const int &param)
	{
		cout<<"Specalized Template called"<<endl;
	}
};
void unary(int param)
{
	cout<<"Overloaded function called"<<endl;
}
int main()
{
	unary(2);
	unary(2.5);
	return 0;	
}
