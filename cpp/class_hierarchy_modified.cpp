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
  Base(){cout<<__func__<<endl;}
#if 0
  ~Base(){cout<<"~"<<__func__<<endl;}
#else 
  virtual ~Base(){cout<<"~"<<__func__<<endl;}
#endif
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
  Derived(){cout<<__func__<<endl;}
#if 0
  ~Derived(){cout<<"~"<<__func__<<endl;}
#else
  virtual ~Derived(){cout<<"~"<<__func__<<endl;}
#endif
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
	//	ptr1->nonVirtualOne();
  ptr1->virtualOne();
  ptr1->virtualTwo();
  ptr1->nonVirtualOne();
  ptr1->nonVirtualTwo();
	}
  else
  {
    cout<<"Cannot dynamic_cast\n";
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
  {
	Base *b = new Base;
	Derived *d = new Derived;
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
	cout<<"runBase with Base ptr\n";
	runBase(b);
  cout<<"-------------------"<<"END"<<"----------------"<<endl;
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
	cout<<"runBase with Derived ptr\n";
	runBase(d);
  cout<<"-------------------"<<"END"<<"----------------"<<endl;
	//runDerived(b); //This is not allowed. If we compile using -fpermissive, it runs like base ptr
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
	cout<<"runDerived with Derived ptr\n";
	runDerived(d);
  cout<<"-------------------"<<"END"<<"----------------"<<endl;

  Base *db = new Derived;
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
  runBase(db);
  cout<<"-------------------"<<"END"<<"----------------"<<endl;
  //runDerived(db);
  
  delete b;
  delete d;

  Base *c = new Derived;
  delete c;
  }
	return 0;
}
