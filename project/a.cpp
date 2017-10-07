#include <iostream>

using namespace std;
//int MyAdd(int,int);
class test
{
	public:
	int a,b;
		test(){a=10;b=20;}
		test(int _a,int _b):a(_a),b(_b){}
		void operator=(const test &obj)
		{
			a=obj.a;
			b=obj.b;
		}
};
int main()
{
	test A(5,6);
	cout<<A.a<<" "<<A.b<<endl;
	test B;
	cout<<B.a<<" "<<B.b<<endl;
	B = A;
	cout<<B.a<<" "<<B.b<<endl;
	//cout<<MyAdd(5,6);
	return 0;
}
