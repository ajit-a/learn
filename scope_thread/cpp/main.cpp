#include <iostream>
#include <stdlib.h>
#include "Main.h"
using namespace std;

//extern "C" int sum(int,int);
int main()
{
	int _a,_b;
	//pthread_t ptid[10];
	pthread_t ptid;
	struct params *p=(struct params *)malloc(sizeof(struct params));
	cout<<"Enter tow numbers"<<endl;
	cin>>_a>>_b;
	p->a=_a;
	p->b=_b;
	pthread_create(&ptid,NULL,sum,p);
	pthread_join(ptid,0); /*If we remove this then main will not wait for thread to finish*/
	//cout<<sum(a,b);
	return 0;
}
