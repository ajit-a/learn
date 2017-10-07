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
	b->B();
	d->B();
	return 0;
}
