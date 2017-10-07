/*http://www.programiz.com/cpp-programming/friend-function-class*/
/*http://www.codersource.net/2010/02/14/c-class-templates/*/
#include <iostream>

using namespace std;

template <class T>
T add(T n1,T n2)
{
	return n1+n2;
}
int main()
{
	int i,j;
	float fi,fj;
	cout<<"Enter 2 integers to add\n";
	cin>>i>>j;
	cout<<"Sum is "<<add(i,j)<<endl;
	cout<<"Enter 2 floats to add\n";
	cin>>fi>>fj;
	cout<<"Sum is "<<add(fi,fj)<<endl;
	return 0;
}
