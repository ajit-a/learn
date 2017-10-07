#include<iostream>
#include "Main.h"
using namespace std;

//extern "C" int sum(int,int);
int main()
{
	int a,b;
	cout<<"Enter tow numbers"<<endl;
	cin>>a>>b;
	cout<<sum(a,b);
	return 0;
}
