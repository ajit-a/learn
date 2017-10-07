#include<stdio.h>

int arr[100],n,n1;

void heapify(int idx)
{
	if(idx==-1 || idx>n1)
		return;
	int tmp,flag=-1;
	int l=2*idx + 1;
	int r=2*idx + 2;
	if(arr[idx]>arr[l] && arr[idx]>arr[r])
	{
		flag=0;
	}
	if(flag==-1)
	{
		if(arr[l]>arr[r] && l<=n1)
		{
			flag=1;
		}
		else
		{
			if(r<=n1)
			flag=2;
		}
		if(flag==-1)
			return;
		else
		{
		printf("Replacing %d with %d for idx:%d and calling heapify\n",arr[idx],arr[2*idx + flag],idx);
		tmp=arr[idx];
		arr[idx]=arr[2*idx + flag];
		arr[2*idx + flag]=tmp;
		display();
		heapify(2*idx + flag);
		}
	}
	else
		heapify(idx-1);
}
void heapsort()
{
	printf("Heapsort called\n");
	int i,tmp;
	for(i=0;i<n-1;i++)
	{
		tmp=arr[n1];
		arr[n1]=arr[0];
		arr[0]=tmp;
		n1--;
		heapify(0);
	}
	tmp=arr[1];
	arr[1]=arr[0];
	arr[0]=tmp;
	display();
}
void display()
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}
int main()
{
	int i;
	printf("Enter the number of elements\n");
	scanf("%d",&n);
	n1=n-1;
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	heapify(n/2 - 1);
	heapsort();
	display();
	return 0;
}	
