#include <iostream>

using namespace std;

class base
{
	public:
		virtual void A(){cout<<"Inside base A\n";}
		void B(){cout<<"Inside base B()\n";}
};
class derived:public base
{
	public:
		virtual void A(){cout<<"Inside derived A\n";}
		void B(){cout<<"Inside derived B()\n";}
};

int main()
{
	base *b = new derived;
	derived *d = new derived;
	b->base::A(); //Calling base class function with base ptr pointing to derived.
	//Here A is virtual hence we had a question how to call base class function. For non-virtual function 
	//it is the default behaviour
	d->A();
	return 0;
}
