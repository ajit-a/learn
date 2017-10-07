#include<stdio.h>

int arr[100],n;

void insertion()
{
	int i,j,tmp;
	for(i=1;i<n;i++)
	{
		tmp = arr[i];
		j = i-1;
		while(j>=0 && arr[j]>tmp) /*Move all elements greater than curr element to right*/
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=tmp;
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
	insertion();
	display();
	return 0;
}	
