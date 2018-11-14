#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	string s("Ajit");
	reverse(s.begin(),s.end());
	cout<<"Reversed s is :"<<s<<endl;
	return 0;
}
