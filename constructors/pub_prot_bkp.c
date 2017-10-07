#include<iostream>
using namespace std;
class Test
{
	private:
		int i;
	public:
		void A();
		Test();
		~Test();
		static Test init();
	//protected:
		void B(Test t);
};
Test::Test()
{
	 i=10;
}
void Test::A()
{
	cout<<"Inside A"<<endl;
}
void Test::B(Test t)
{
	cout<<"Inside B and i is "<<t.i<<endl;
}
Test::~Test()
{
}

int main()
{
	Test t1,t2;
	t1.A();
	t2.B(t1);
	
	return 0;
}
