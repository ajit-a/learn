#include<stdio.h>

int arr[100],n,n1;

static int _d=1;
void heapify(int idx)
{
	//printf("called %s\n",__FUNCTION__);
	int l=(idx*2)+1;
	int r=(idx*2)+2;
	int _t,_tmp;
	if(idx<0)return;
	if(l>=n1) return;
	if(r>=n1) return;
	else if(n1!=n && _d==0){r=l;_d++;}
	//if(r >= n1 || idx <0)return;
	if(arr[l]>arr[r])
		_t=l;
	else
		_t=r;
	if(arr[_t]>arr[idx])
	{
		_tmp=arr[idx];
		arr[idx]=arr[_t];
		arr[_t]=_tmp;
		//display();
		heapify(_t);
	}
	heapify(idx-1);
	display();
}

void heapsort()
{
	printf("Heapsort called\n");
	int i,tmp;
	for(i=0;i<n-1;i++)
	{
		//if(arr[n1-1]<arr[0]){
		_d=0;
		printf("i:%d n1:%d\n",i,n1);
		tmp=arr[n1-1];
		arr[n1-1]=arr[0];
		arr[0]=tmp;
		n1--;
		heapify(0);
		//}
	}
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
	n1=n;
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	heapify(n/2 - 1);
	heapsort();
	display();
	return 0;
}	
