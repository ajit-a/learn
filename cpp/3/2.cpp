#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	string s;
	cin>>s;
	string s1(s);
	reverse(s.begin(),s.end());
	if(s == s1)
		cout<<"Palindrome"<<endl;
	else
		cout<<"Not a Palindrome"<<endl;
	return 0;
}
