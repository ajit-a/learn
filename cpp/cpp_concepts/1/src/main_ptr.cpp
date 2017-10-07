#include <iostream>
#include "main.hpp"
#include <memory>

using namespace std;
int MyClass::getVal()
{
	return this->a;
}
void MyClass::setVal(const int &b)
{
	this->a=b;
}
MyClass::MyClass()
{
}
MyClass::~MyClass()
{
}
int main()
{
	//MyClass obj;
	auto_ptr<MyClass> obj(new MyClass());
	int num;
	cin>>num;
	obj->setVal(num);
	int c=obj->getVal();
	cout<<"c:"<<c<<endl;
	return 0;
}
