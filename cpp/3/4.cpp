#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	string s;
	getline(cin,s);
	s.erase(remove_if(s.begin(),s.end(),[](auto a){return a==' '||a==',';}),s.end());
	string s1(s);
	reverse(s.begin(),s.end());
	if( equal(s.begin(),s.end(),s1.begin(),[](auto a,auto b){return tolower(a)==tolower(b);}) )
		cout<<"Palindrome"<<endl;
	else
		cout<<"Not a Palindrome"<<endl;
	return 0;
}
