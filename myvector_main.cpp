#ifdef UPTR
#include "myvector_uptr.h"
#else
#include "myvector.h"
#endif
#include <iostream>

using namespace std;

class Test
{
	public:
		int _val;
		Test(int val):_val(val){cout<<"ctor called for:"<<_val<<endl;}
		~Test(){cout<<"Dtor called for:"<<_val<<endl;}
		auto begin() const {return 0;}
		auto end() const {return 0;}
};

int main()
{
	try 
	{
		MyVector<Test*> v;
		v.push_back(new Test(10));
		v.push_back(new Test(20));
		v.push_back(new Test(30));
		std::cout<<v[1]->_val<<std::endl;
		std::cout<<v.size()<<std::endl;
		std::cout<<v.capacity()<<std::endl;
		MyVector<Test*> v1(v);
	}
	catch(const std::exception &e)
	{
		std::cout<<e.what()<<std::endl;
	}
	catch(const char *e)
	{
		std::cout<<e<<std::endl;
	}
	return 0;
}
