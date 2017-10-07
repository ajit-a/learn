#include<iostream>
#include<map>
#include<list>
using namespace std;

typedef map< int, map< string,int > > mymap;
	
map< string,list<string> >m;
map< int, map< string,int > >m1;

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
void fillm1()
{
	m1[121]["Minor"] = 21;
	m1[121]["Major"] = 25;
	m1[121]["Critical"] = 30;
	m1[122]["Major"] = 23;
	m1[123]["Critical"] = 25;
	
	string s="Minor";
	cout<<m1[121][s]<<endl;

	for(mymap::iterator itr=m1.begin();itr!=m1.end();itr++)
	{
		//cout<<(*itr)[121]["Minor"]<<endl;
	}
	for(map< int,map<string,int> >::iterator itr1=m1.begin();itr1!=m1.end();++itr1)
	{
		for(map<string,int>::iterator itr2=(*itr1).second.begin();itr2!=(*itr1).second.end();++itr2)
		{
			cout<<(*itr2).first<<" "<<(*itr2).second<<endl;
		}
	}
}
int main()
{
	/*list<string> l;
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
	display(select);*/
	fillm1();
}
