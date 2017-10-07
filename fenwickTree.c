/*http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _MAX 1000

typedef struct node
{
	int cF;
	struct node *left;
	struct node *right;
}node;

int Tree[_MAX];
int N;
int check()
{
	int i;
	for(i=1;i<=N;i++)
		printf("%d ",Tree[i]);
	printf("\n");
}
int cumSum(int n)
{
	int _sum=0;
	while(n > 0)
	{
		_sum += Tree[n];
		n -= (n & -n);
	}
	return _sum;
}
int main()
{
	int i;
	int in[_MAX];
	int j;
	scanf("%d",&N);
	scanf("%d",&in[1]);
	for(i=2;i<=N;i++)
	{
		scanf("%d",&in[i]);
	}
	memset(Tree,0,sizeof(Tree));
	for(i=N;i>0;i--)
	{
		#ifdef debug
		printf("i:%d\n",i);
		printf("i & -i:%d\n",(i & -i));
		printf("i- (i & -i):%d\n",(i-(i & -i)));
		#endif
		int k;
		k=(i-(i & -i));
		j=i;
		while(j>k)
		{
			Tree[i]+=in[j--];
		}
	}
	//check();
	printf("Enter index\n");
	scanf("%d",&i);
	printf("%d\n",i);
	printf("cumSum:%d\n",cumSum(i));
	return 0;
}
