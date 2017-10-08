#include <iostream>

using namespace std;


class A
{
		static int objectCount;
	public:
		static void* operator new[](size_t tz)
		{
			auto p = ::new A;
			++A::objectCount;
			if(A::objectCount>10)
				throw bad_alloc();
			return p;
		}
		void static CleanUp(A*);
};
int A::objectCount=0;
void A::CleanUp(A *a)
{
	cout<<"Doing cleanup"<<endl;
	delete a;
}

int main()
{
	A* arr[100];
	for (int i=12;i>0;--i)
	{
		try
		{
			arr[i]  = new A[i];
		}
		catch(...)
		{
			cout<<"Caught exception"<<endl;
			A::CleanUp(arr[i]);
		}
		cout<<"i:"<<i<<endl;
	}
}
