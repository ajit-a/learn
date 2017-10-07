#include<iostream>
using namespace std;
class Test
{
	private:
		int i;
		static Test t;
	public:
		void A();
		Test();
		~Test();
		static Test init();
	//protected:
		void B(Test t);
};
Test Test::init()
{
	//Test t;
	t=new Test();
	return t;
}
Test::Test()
{
	int i=10;
}
void Test::A()
{
	cout<<"Inside A"<<endl;
}
void Test::B(Test t)
{
	cout<<"Inside B"<<endl;
}
Test::~Test()
{
}

int main()
{
	//Test t;
	Test::init();
	t.A();
	t.B(t);
	
	return 0;
}
