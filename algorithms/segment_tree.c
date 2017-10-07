#include <stdio.h>

#define MAX 100
#define INF -9999

int tree[4*MAX]; /*Hold seg tree for addition of a range with start index as 0*/
int arr[MAX];
void Create_seg_tree(int l,int r, int pos)
{
	if(l==r)
	{
		tree[pos]=arr[l];
		return;
	}
	int mid=(l+r)/2;
	Create_seg_tree(l,mid,(2*pos)+1);
	Create_seg_tree(mid+1,r,(2*pos)+2);
	tree[pos]=tree[2*pos + 1] + tree[2*pos + 2];
}
int Query_seg_tree(int l,int r,int ql,int qr,int pos)
{
	if(ql<=l && qr >=r) /*Total overlap*/
		return tree[pos];
	if(ql > r || qr < l)/*No overlap*/
		return 0;/*0 because the implementation is for sum*/
	int mid=(l+r)/2;
	return Query_seg_tree(l,mid,ql,qr,(2*pos)+1)+Query_seg_tree(mid+1,r,ql,qr,(2*pos)+2);
}
int main()
{
	int i,l,r;
	for(i=0;i<5;i++)arr[i]=i+1;
	Create_seg_tree(0,4,0);
	scanf("%d %d",&l,&r);
	printf("%d\n",Query_seg_tree(0,4,l,r,0));
	for(i=0;i<8;i++)printf("%d ",tree[i]);printf("\n");
	return 0;
}
