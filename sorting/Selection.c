#include<stdio.h>

int arr[100],n;

/*Find the min element and place it in the left (sorted) array*/
void selection()
{
	int i,j,tmp,_minidx;
	for(i=0;i<n-1;i++)
	{
		_minidx=i;//Current index is the index of min element
		for(j=i+1;j<n;j++)
		{
			if(arr[j]<arr[_minidx])
			{
				_minidx=j; //If this element is smaller then save the index for swapping
			}
		}
		tmp=arr[i];
		arr[i]=arr[_minidx];
		arr[_minidx]=tmp;
		display();
	}
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
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	selection();
	display();
	return 0;
}	
