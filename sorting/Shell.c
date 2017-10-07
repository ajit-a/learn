#include<stdio.h>

int arr[100],n;

/*Shell sort is a modified insertion sort where we perform insertion sort with sub-arrays formed with a gapped factor.
 * This help is moves far elements near to their desired positions*/
void shell()
{
	int i,j,tmp,gap;
	for(gap=n/2 ; gap>0 ; gap--)
	{
		for(i=gap ; i < n ; i++)
		{
			tmp = arr[i];
		#if 0
			for(j=i; j>=gap && arr[j-gap] > tmp ; j-=gap)
			{
				arr[j]=arr[j-gap];
			}
			arr[j]=tmp;
		#else //This is analogous to our insertion sort program
			for(j=i-gap; j>=0 && arr[j] > tmp ; j-=gap)
			{
				arr[j+gap]=arr[j];
			}
			arr[j+gap]=tmp;
		#endif
			printf("gap:%d ",gap);
			display();
		}
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
	shell();
	display();
	return 0;
}	
