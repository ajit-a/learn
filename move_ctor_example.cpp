#include <iostream>
#include <vector>

//This shows sample of copy ctor if we have raw ptr and a vector

using namespace std;

class A
{
	private:
		int *ptr;
		vector<int> v;
	public:
		A(int *p,vector<int> & myvec):ptr(p),v(myvec){}

		A(A &&a)
		{
			ptr = std::move(a.ptr);
			v = std::move(a.v);
			a.ptr = nullptr;
		}
		void display()
		{
			if(nullptr != ptr)
				cout<<"ptr value is : "<<*ptr<<endl;
			else
				cout<<"ptr is nullptr"<<endl;
			cout<<"vetor items are :: ";
			for(auto &item:v)
			{
				cout<<item<<" ";
			}
			cout<<endl;
		}
};
int main()
{
	int val=5;
	int *p=&val;
	vector<int> v ={5,4,3,2};
	A a(p,v);

	a.display();

	A b(std::move(a));
	b.display();
	a.display();
	return 0;
}

