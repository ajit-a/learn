#ifndef _MAIN_HPP_
#define _MAIN_HPP_
class MyClass
{
	protected:
		int a;
	public:
		MyClass();
		~MyClass();
		//void setVal(int a);
		void setVal(const int &a);
		int getVal();
};
#endif
