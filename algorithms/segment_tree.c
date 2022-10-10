#include <stdio.h>

#define MAX 1000
#define INF -99999

int tree[4*MAX]; /*Hold seg tree for addition of a range with start index as 0*/
int arr[MAX];
int N=5;
int max_idx_tree=0;
void printTree()
{
	printf("Tree :\n");
	int i=0;
	for(;i<=max_idx_tree;i++)
	{
		printf("%d ",tree[i]);
	}
	printf("\n");
}
void Create_seg_tree(int l,int r, int pos)
{
    max_idx_tree = pos > max_idx_tree ? pos : max_idx_tree;
	if(l==r)
	{
	    printf("..Updating pos:%d with val:%d\n",pos,arr[l]);
		tree[pos]=arr[l];
		return;
	}
	int mid=(l+r)/2;
	Create_seg_tree(l,mid,(2*pos)+1);
	Create_seg_tree(mid+1,r,(2*pos)+2);
	printf("Updating pos:%d with val:%d\n",pos,tree[2*pos + 1] + tree[2*pos + 2]);
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
void update(int l,int r,int segidx,int idx,int val)
{
    if(l == r) {
        arr[idx] += val;
        tree[segidx] += val;
        //printf("Updated pos:%d with val:%d\n",segidx,tree[segidx]);
        return;
    }
    int mid = (l + r) / 2;
    if (l <= idx && idx <= mid) {
        update(l,mid,2*segidx + 1,idx,val);
    }
    else {
        update(mid+1,r,2*segidx + 2,idx,val);
    }
    tree[segidx] = tree[segidx*2 + 1] + tree[segidx*2 + 2];
    //printf("..Updating pos:%d with val:%d\n",segidx,tree[segidx]);
}
int main()
{
	int i,l,r;
	for(i=0;i<N;i++)arr[i]=i+1;
	for(i=0;i<N;i++)printf("%d ",arr[i]);printf("\n");
	Create_seg_tree(0,N-1,0);
	for(i=0;i<=max_idx_tree;i++)printf("%d ",tree[i]);printf("\n");
	printf("max_idx_tree:%d\n",max_idx_tree);
	while(true) {
	scanf("%d %d",&l,&r);
	printf("%d\n",Query_seg_tree(0,N-1,l,r,0));
	for(i=0;i<=max_idx_tree;i++)printf("%d ",tree[i]);printf("\n");
	scanf("%d %d",&l,&r);
	update(0,N-1,0,l,r);
	for(i=0;i<=max_idx_tree;i++)printf("%d ",tree[i]);printf("\n");
	}
	return 0;
}
