#include <iostream>

using namespace std;

class Base
{
private:
	int i;
public:
	virtual void virtualOne()
	{
		cout<<"Base::"<<__func__<<endl;
	}
	virtual void virtualTwo()
	{
		cout<<"Base::"<<__func__<<endl;
	}
	void nonVirtualOne()
	{
		cout<<"Base::"<<__func__<<endl;
	}
	void nonVirtualTwo()
	{
		cout<<"Base::"<<__func__<<endl;
	}
};
class Derived: public Base
{
private:
	int i;
public:
	void virtualOne() override
	{
		cout<<"Derived::"<<__func__<<endl;
	}
	void nonVirtualOne()
	{
		cout<<"Derived::"<<__func__<<endl;
	}
};
void runBase(Base *ptr)
{
  ptr->virtualOne();
  ptr->virtualTwo();
  ptr->nonVirtualOne();
  ptr->nonVirtualTwo();
	if(dynamic_cast<Derived*>(ptr) != nullptr)
	{
		auto ptr1 = dynamic_cast<Derived*>(ptr);
		cout<<"Here..."<<endl;
		ptr1->nonVirtualOne();
	}
}
void runDerived(Derived *ptr)
{
  ptr->virtualOne();
  ptr->virtualTwo();
  ptr->nonVirtualOne();
  ptr->nonVirtualTwo();
}
int main()
{
	Base *b = new Base;
	Derived *d = new Derived;
	cout<<"runBase with Base ptr\n";
	runBase(b);
	cout<<"runBase with Derived ptr\n";
	runBase(d);
	//runDerived(b); //This is not allowed. If we compile using -fpermissive, it runs like base ptr
	cout<<"runDerived with Derived ptr\n";
	runDerived(d);
	return 0;
}
