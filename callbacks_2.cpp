#include <iostream>

using namespace std;

typedef int (*callback)(int,int);


int process(callback cb,int a,int b)
{
	return cb(a,b);
}

int add(int a,int b)
{
	return a+b;
}
int main()
{
	cout<<process(add,2,3)<<endl;
	return 0;
}
