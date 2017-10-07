#include<iostream>
#include<stdlib.h>

using namespace std;

template <class T>
class MY
{
	public:
		T *data;
		MY()
		{
			//data = (T*)malloc(sizeof(T));
			data = new(T);
		}
};

typedef struct node
{
	int a;
	char b;
}MNODE;

int main()
{
	MY<MNODE> obj;
	obj.data->a=5;	
	obj.data->b='a';
	cout<<obj.data->a<<endl;
	cout<<obj.data->b<<endl;
	return 0;	
}
