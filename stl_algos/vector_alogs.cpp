#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int gi=0;
vector<int> v;
vector<int>::iterator itr;
void Menu()
{
	cout<<"1.Learn adjacent_find()\n";
	cout<<"2.Learn count()\n";
	cout<<"3.Learn count_if()\n";
	cout<<"4.Learn equal()\n";
	cout<<"5.Learn find() and find_end()\n";
	cout<<"6.Learn for_each()\n";
	cout<<"7.Learn mismatch()\n";
	cout<<"8.Learn search() and search_n()\n";
}
void vADJ()
{
	int i;
	//cin>>i;
	itr  = adjacent_find(v.begin(),v.end());
	cout<<"First repeating element is :";
	cout<<*itr<<endl;
	itr  = adjacent_find(v.begin(),v.end(),[](int a,int b){if(b>a)return true;else return false;});
	cout<<"First element as per lambda  b>a is :";
	cout<<*itr<<endl;
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
				vADJ();
				break;
			case 2:
				cout<<"Enter the value to cout\n";
				cin>>i;
				cout<<"count of "<<i<<" is : "<<count(v.begin(),v.end(),i)<<endl;
				break;
			case 3:
				cout<<"count of lambda a%2 is : "\
				<<count_if(v.begin(),v.end(),[](int a){if(a%2==0)return true;else return false;})<<endl;
				break;
			case 4:
				cout<<"Range 0-1,2-3 are : "\
				<<equal(v.begin(),v.begin()+1,v.begin()+2,[](int a,int b){if(a==b)return true;else return false;})<<endl;
				break;
			case 5:
				{
				cout<<"Enter a number to find its first occurance : ";
				cin>>i;
				itr = find(v.begin(),v.end(),i);
				cout<<"itr placed at : "<<*itr<<endl;

				cout<<"Enter the number of elements in range to find its occurance : ";
				cin>>j;
				vector<int> v1;
				while(j--)
				{
					cin>>i;
					v1.push_back(i);
				}
				itr = find_end(v.begin(),v.end(),v1.begin(),v1.end());
				cout<<"itr placed at first element of last occurance for given range : "<<*itr<<endl;
				}
				break;
			case 6:
				cout<<"Enter the value to be added to each element : ";
				cin>>gi;
				for_each(v.begin(),v.end(),[](int &a){a = a+gi;});
				cout<<"Vector (v) now :";
				for_each(v.begin(),v.end(),[](int a){cout<<a<<' ';});
				cout<<endl;
				break;
			case 7:
				{

				cout<<"Enter the number of elements in range to find mismatch : ";
				cin>>j;
				vector<int> v1;
				while(j--)
				{
					cin>>i;
					v1.push_back(i);
				}
				pair<vector<int>::iterator, vector<int>::iterator > mypair;
				mypair = mismatch(v.begin(),v.end(),v1.begin());
				cout<<"first set of mismatched elements (default comparison) is : "<<*(mypair.first)<<" and "<<*(mypair.second)<<endl;
				mypair = mismatch(v.begin(),v.end(),v1.begin(),[](int i,int j){if(i<=j)return true;else return false;});
				cout<<"first set of mismatched elements (predicate i<=j comparison) is : "<<*(mypair.first)<<" and "<<*(mypair.second)<<endl;
				}
			case 8:
				{

				cout<<"Enter the number of elements in the pattern to search : ";
				cin>>j;
				vector<int> v1;
				while(j--)
				{
					cin>>i;
					v1.push_back(i);
				}
				itr = search(v.begin(),v.end(),v1.begin(),v1.end());
				cout<<"itr set to first elements (default comparison) : "<<*itr<<endl;
				itr = search(v.begin(),v.end(),v1.begin(),v1.end(),[](int i,int j){if(i<=j)return true;else return false;});
				cout<<"itr set to first element (predicate i<=j comparison) of matched seq : "<<*itr<<endl;
				}
			case 9:
				{
					itr = find_if(v.begin(),v.end(),[](int a){if(a>gi){gi=a;return false;} else return false;});
					cout<<"Max element using find_if is : "<<gi<<endl;
					itr = max_element(v.begin(),v.end());
					cout<<"Max element using max_element is : "<<gi<<endl;
				}
				
		}
		cin>>choice;
	}
	return 0;
}
