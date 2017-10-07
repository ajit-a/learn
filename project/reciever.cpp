#include "queue.hpp"
#include <iostream>

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
int main()
{
	while(1)
        {
                LLnode<NODE> *p = QUEUE.pop();
		if(p)
                	cout<<p->data->weight<<endl;
        }
        return 0;
}
