#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
	string a;
	cout<<"Enter your name"<<endl;
	cin>>a;
	cout<<"Welcome, "<<a<<endl;
	cout<<"Enter your name again "<<endl;
	fflush(0);
	getline(cin,a);
	string b;
	getline(cin,b);
	cout<<"Welcome, "<<a<<endl;
	cout<<"Welcome, "<<b<<endl;
	return 0;
}
