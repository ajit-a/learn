#include <iostream>

using namespace std;

class Test
{
};

int main()
{
	Test t;
	Test *t1 = new Test;
	cout<<"Size of t:"<<sizeof(t)<<endl;
	cout<<"Size of t1:"<<sizeof(t1)<<endl;
	if(t1)
		delete t1;
	return 0;
}

//How to avoid object being created using Test t ?
//mark dtor as private
