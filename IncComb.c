#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int *pointers[10];
int arr[MAX],N,n;
int digits[10];
int nDigits;
int nPointers;

int compare(const int *a,const int *b)
{
	if(*a==*b)
		return 0;
	if(*a<*b)
		return -1;
	else
		return 1;
}
int printCombinations()
{
	int i,j;
	int k=nDigits;
	while(k)
	{
		int num=0;
		for(i=0;i<k-1;i++)
		{
			num+=(*pointers[i] * 10);
		}	
		j=k-1;
		while(j<nPointers && *pointers[j]!=arr[n])
		{
			num+=(*(pointers[j]) * 10);
			if(num<=N)
				printf("%d\n",num);
			pointers[j]++;
		}
		k--;
	}
}
int main()
{
	printf("Enter N:");
	scanf("%d",&N);
	printf("Enter the no of array digits :");
	scanf("%d",&n);
	printf("Enter the array digits :");
	int i=0;
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);	
	}
	qsort(arr,n,sizeof(int),compare);
	int tmp=N;
	i=n;
	nDigits=0;
	while(tmp)
	{
		digits[--i]=tmp%10;
		tmp/=10;
		nDigits++;
	}
	i=0;
	int j=nDigits;
	nPointers=0;
	while(j)
	{
		int p=0;
		while(digits[j-1]!=arr[p] && p<n)(p++);
		if(p!=n)
		{
			pointers[i]=&arr[p];
			i++;
			nPointers++;
		}
		j--;
	}	
	printCombinations();
	return 0;
}
