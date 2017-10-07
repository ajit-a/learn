#include <iostream>

using namespace std;

class base
{
	public:
		virtual void A(){cout<<"Inside base A\n";}
		void C(){cout<<"Inside base C()\n";}
};
class derived:public base
{
	public:
		virtual void A(){cout<<"Inside derived A\n";}
		void D(){cout<<"Inside derived D()\n";}
};

int main()
{
	base *b = new derived;
	derived *d = new derived;
	//b->D(); Cannot do this
	d->D();

	derived *castedPtr = dynamic_cast<derived*>(b);
	castedPtr->D();
	return 0;
}
