#include <iostream>

using namespace std;

class base
{
	public:
		virtual void A(){cout<<"Inside base A\n";}
};
class derived:public base
{
	public:
		virtual void A(){cout<<"Inside derived A\n";}
};

int main()
{
	base *b = new base;
	derived *d = new derived;
	b->A();
	d->A();
	return 0;
}
