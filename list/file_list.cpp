#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

using namespace std;

int main()
{
	string comm,path;
	string tmp;
	char fin[100]={0},line[256]={0};
	char *type="r";
	int i;
	FILE *f;
	string final[10000];
	cout<<"Enter the path"<<endl;
	cin>>path;
	//cout<<"Path is "<<path<<endl;
	comm="ls";
	tmp=comm+" "+path;
	//cout<<"Length is "<<tmp.length()<<endl;
	for(i=0;i<tmp.length();i++)
		fin[i]=tmp[i];

	f=(FILE*)popen(fin,"r");
	
	i=0;
	//while (fread(line,1,sizeof(*f) ,f))
	while (fgets(line,sizeof(*f) ,f))
	{
		//cout<<line;
		final[i++]=line;
		//cout<<final[i-1]<<endl;
	//cout<<"i is "<<i<<endl;
	}
	//cout<<"i is "<<i<<endl;
	while(--i)
		cout<<final[i];

	//system(fin);
}
