#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

int main()
{
	string comm,inp;
	char list[100]={0},line[256]={0};
	char *p;
	FILE *f;
	string fin[1000];
	int i=0;
	comm="ls";
	cout<<"Enter the path"<<endl;
	cin>>inp;
	comm=comm+" "+inp;
	cout<<comm<<endl;

	for(i=0;comm[i];i++)
		list[i]=comm[i];
	p=list;
	
	f=popen(p,"r");
	i=0;
	while(fgets(line,sizeof(*f),f))
	{
		fin[i]=line;
		i++;
	}
	//system(p);
	
}
