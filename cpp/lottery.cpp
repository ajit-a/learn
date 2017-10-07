#include <iostream>
#include <stdlib.h>

using namespace std;

void lottery(int totaln,int cn)
{
	if(totaln < cn)
		return;
	srand(time(0));
	int *lot = new int(cn);
	for(int i=0;i<cn;i++)
	{
		lot[i]=rand()%totaln + 1;
		for(int j=0;j<i;j++)
		{
			if(lot[i]==lot[j])
			{
				i--;
				break;
			}
			else if(i==j)
				cout<<lot[i]<<endl;
		}
	}
	
}
int main()
{
	lottery(49,6);
	return 0;
}
