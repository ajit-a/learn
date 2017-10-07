#include "queue.hpp"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#define MAX 10
using namespace std;
typedef struct node
{
	int a;
	uint weight;
}NODE;

template< typename T>
void copyNodeData(T &dst,T &src)
{
	dst->weight = src->weight;
	dst->a = src->a;
}
MyPQ<NODE> QUEUE(100);
void reciever()
{
	while(1)
        {
                LLnode<NODE> *p = QUEUE.pop();
		if(p)
                cout<<p->data->weight<<endl;
        }
}
int main()
{
        int i,j;
	int pid=fork();
	//if(pid!=0)
	//	exit(0);
        for(i=0,j=MAX;i<MAX;i++,j--)
        {
                node n;
                n.a=i;
                n.weight=j;
                //cin>>n.weight;
                QUEUE.push(&n);
        }
        /*for(i=0;i<MAX;i++)
        {
                LLnode<NODE> *p = QUEUE.pop();
                cout<<p->data->weight<<endl;
        }*/
        return 0;
}
