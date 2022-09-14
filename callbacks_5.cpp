#include <iostream>
#include <functional>

//typedef std::function<int(int,int)> callback;

int process(std::function<int(int,int)> cb,int a,int b)
{
	return cb(a,b);
}

int add(int a,int b)
{
	return a+b;
}

int main()
{
	std::cout<<process(add,5,6)<<std::endl;
	return 0;
}
