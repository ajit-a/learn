#ifndef _MAIN_HPP_
#define _MAIN_HPP_
#include <memory>
class MyClass
{
	protected:
		int a;
	public:
		MyClass();
		~MyClass();
		//void setVal(int a);
	//protected:
		void setVal(MyClass &a);
		int getVal(MyClass &a);
};
#endif
