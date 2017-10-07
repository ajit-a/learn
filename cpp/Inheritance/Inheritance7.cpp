#include "general.h"

class Base
{
	private:
		int a;
	public:
		Base(int arg=0):a(arg){cout<<"Base ctor called\n";}
		void public_fun()
		{
			cout<<"a:"<<a<<endl;
		}
	protected:
		void protected_fun()
		{
			cout<<"a:"<<a<<endl;
		}
};
class Derived:public Base
{
	public:
		Derived(int arg=0):Base(arg){cout<<"Derived ctor called\n";}
		void interface_to_access_protectedFun()
		{
			protected_fun();
		}
};

int main()
{
	unique_ptr<Derived> dPtr = make_unique<Derived>(100);
	dPtr->public_fun();
	//dPtr->protected_fun(); //Error
	dPtr->interface_to_access_protectedFun();
	return 0;
}
