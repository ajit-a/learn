#include<iostream>
#include<map>
#include<list>

using namespace std;
map< string,list<string> >m;

void display(string s)
{
		if((m[s]).empty()){cout<<"No such entry"<<endl;return;}
		for(list<string>::iterator ii=m[s].begin();ii!=m[s].end();++ii)
		{
			cout<<(*ii)<<endl;
		}
}
void _display(string s)
{
	for(map< string,list<string> >::iterator i=m.begin();i!=m.end();++i)
	{
		for(list<string>::iterator ii=(*i).second.begin();ii!=(*i).second.end();++ii)
		{
			cout<<(*ii)<<endl;
		}
	}
}
void addToListOfMap(string lhs,string rhs)
{
	m[lhs].push_back(rhs);
}
/*void addTomap(string lhs,string rhs)
{
	if((m[lhs]).empty())
	{
		//m.insert(lhs);
		addToList(lhs,rhs);
	}
	else
	{
		addToList(lhs,rhs);
	}
}*/

int main()
{
	list<string> l;
	l.push_back("ajit");
	l.push_back("mait");
	m["first"]=l;
	l.clear();
	l.push_back("three");
	l.push_back("four");
	m["seco"]=l;
	l.clear();
	string select,lhs,rhs;
	cout<<"Enter LHS"<<endl<<"Enter list element"<<endl;
	cin>>lhs>>rhs;
	addToListOfMap(lhs,rhs);
	cout<<"Enter selection"<<endl;
	cin>>select;
	display(select);
}
