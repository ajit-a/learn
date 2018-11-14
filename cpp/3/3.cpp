#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	string s;
	cin>>s;
	#if 0
	string s1(s);
	reverse(s.begin(),s.end());
	if( equal(s.begin(),s.end(),s1.begin(),[](auto a,auto b){return tolower(a)==tolower(b);}) )
		cout<<"Palindrome"<<endl;
	else
		cout<<"Not a Palindrome"<<endl;

	#else
	transform(s.begin(),s.end(),s.begin(),[](auto a){return tolower(a);});
	string s1(s);
	reverse(s.begin(),s.end());
	if(s==s1)
		cout<<"Palindrome"<<endl;
	else
		cout<<"Not a Palindrome"<<endl;
	#endif
	return 0;
}
