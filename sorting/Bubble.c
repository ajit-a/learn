#include<stdio.h>

int arr[100],n;

/*Keep moving the largest element to right*/
/*Can be optimized by checking if there is any swapping done in the inner loop, if no swapping means already sorted*/
void bubble()
{
	int i,j,tmp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++) //Since we are placing the largest element to right, we can skip last i elements
		{
			if(arr[j+1]<arr[j])
			{
				tmp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = tmp;
			}
		}
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
	bubble();
	display();
	return 0;
}	
