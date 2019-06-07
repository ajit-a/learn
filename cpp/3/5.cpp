#include <iostream>

using namespace std;

int main()
{
	string one("I walked down the canyon with the moving mountain bikers.");
	string two("The bikers passed by me too close for comfort.");
	string three("I went hiking instead.");

	auto it = one.find("walked");
	if(it != string::npos)
		one.replace(it,6,"moved");
	it = one.find("moving");
	if(it != string::npos)
		one.replace(it,7,"");

	two.insert(4,"mountain ");
	cout<<one<<endl;
	cout<<two<<endl;
	return 0;
}
