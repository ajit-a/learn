#include <iostream>

using namespace std;

class Test
{
	void* operator new(const size_t s){}
	void* operator new[](const size_t s){}
};

int main()
{
	Test t;
	Test *t1 = new Test;
	Test *t2 = new Test[10];
	cout<<"Size of t:"<<sizeof(t)<<endl;
	cout<<"Size of t1:"<<sizeof(t1)<<endl;
	if(t1)
		delete t1;
	return 0;
}

//How to avoid object being created using new ?
//mark new operator as private
