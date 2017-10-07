/*This implementation is for RU PQ
 * refer http://zobayer.blogspot.in/search/label/binary%20indexed%20tree
 * */
#include<stdio.h>

#define MAX 100002
typedef unsigned long long ULL;

long long A[MAX];
unsigned long long sum[MAX];
int N;

void create_Feny_tree()
{
	int idx=1;
	for(idx=2;idx<=N;idx+=2) /*Only even indices are required to be updated*/
	{
		A[idx]=sum[idx]-sum[idx - (idx&-idx)];
	}
}
void printTree()
{
	printf("Tree :\n");
	int i=1;
	for(;i<=N;i++)
	{
		printf("%lld ",A[i]);
	}
	printf("\n");
}
void updateIndex(int idx,long long v)
{
	while(idx<=N)
	{
		A[idx] += v;
		idx += idx & (-idx);
	}
}
ULL sumRange(int l,int r)
{
	int idx=r;
	unsigned long long _S=0;
	while(idx>=l)
	{
		_S += A[idx];
		idx -= idx & (-idx);
	}
	return _S;
}
int main()
{
	int i,j;
	printf("Enter elements (N):\n");
	scanf("%d",&N);
	printf("Enter the elements\n");
	sum[0]=A[0]=0;
	for(i=1;i<=N;i++)
	{
		scanf("%lld",&A[i]);
		sum[i]=A[i]+sum[i-1];
	}
	printTree();
	create_Feny_tree();	
	printTree();
	while(1){
	long long v;
	printf("Enter the index to update (idx) and value (v): ");
	scanf("%d %lld",&i,&v);
	updateIndex(i,v);
	printTree();
	int l,r;
	printf("Enter the range to query (l,r): ");
	scanf("%d%d",&l,&r);
	printf("Sum is %lld\n",sumRange(l,r));
	}
	return 0;
}
