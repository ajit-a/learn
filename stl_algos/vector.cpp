#include <iostream>
#include <vector>

using namespace std;

vector<int> v;
void Menu()
{
	cout<<"1.Learn vector at()\n";
	cout<<"2.Learn vector back()\n";
	cout<<"3.Learn vector begin()\n";
	cout<<"4.Learn vector capacity() and size()\n";
	cout<<"5.Learn vector erase()\n";
	cout<<"6.Learn vector insert()\n";
	cout<<"7.Learn vector pop_back()\n";
	cout<<"8.Learn vector resize()\n";
}
void vAT()
{
	cout<<"Enter an index\n";
	int i;
	cin>>i;
	cout<<"Value at "<<i<<" is "<<v.at(i)<<endl;
}
int main()
{
	int n,j,i;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>j;
		v.push_back(j);
	}
	Menu();
	int choice;
	cin>>choice;
	while(1)
	{
		switch(choice)
		{
			case 1:
				vAT();
				break;
		}
	}
	return 0;
}
