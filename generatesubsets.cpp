#include <iostream>

using namespace std;

void generate()
{
	int max_possiblities=8;
	int N=3;
	for(int i=0;i<max_possiblities;++i)
	{
		cout<<i<<endl;
		for(int index=0;index<N;++index)
		{
		cout<<index<<endl;
			//if(i&(1<<index))
				cout<<i<<" "<<(1<<index)<<" "<<(i&(1<<index))<<endl;
				//cout<<1<<" ";
			//else
			//	cout<<0<<" ";
		}
		cout<<endl<<"-----------------"<<endl;
	}
}
int main()
{
	generate();
	return 0;
}
