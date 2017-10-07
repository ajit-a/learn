#include <iostream>
#include <vector>

using namespace std;

typedef vector<int>::iterator ivitr;


int main()
{
	vector<int> v;
	int i;
	while(cin>>i)v.push_back(i);
	ivitr itr = v.begin();
	int min=*itr;
	int profit = 0;
	int tprofit=0;
	int pos1=0,pos2=0;

	advance(itr,1);
	
	for(i=1;itr!=v.end();++itr,++i)
	{
		if(*itr < min)
		{
			min = *itr;
			pos1 = i;
			continue;
		}
		//profit = (*itr - min) > profit ? (*itr - min) : profit;
		tprofit = (*itr - min);
		if(tprofit >= profit)
		{
			profit = tprofit;
			pos2 = i;
		}
	}
	cout<<profit<<"Buy at:"<<pos1<<" Sell at :"<<pos2<<endl;
	return 0;
}
