#include <iostream>
#include "main.hpp"
#include <memory>

using namespace std;
int MyClass::getVal(MyClass &a)
{
	//return this->a;
}
void MyClass::setVal(MyClass &a)
{
	//this->a=a;
}
MyClass::MyClass()
{
}
MyClass::~MyClass()
{
}
int main()
{
	//MyClass obj,obj1;
	auto_ptr<MyClass> obj(new MyClass());
	auto_ptr<MyClass> obj1(new MyClass());
	int num;
	cin>>num;
	obj->setVal(obj1);
	int c=obj->getVal(obj1);
	cout<<"c:"<<c<<endl;
	return 0;
}
