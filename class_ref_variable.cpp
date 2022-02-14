//Can a class have reference variable ?
#include<iostream>
class A
{
	private:
		const int &i;
	public:
		A(const int &j=0):i(j){
			std::cout<<"ctor:"<<i<<"\n";
		}
		A(const int &&) = delete;
		void fund(){std::cout<<"Hello\n";}
};

int main()
{
	int k=2;
	A a{k};
	A b{int(3)};
	a.fund();
	return 0;
}
