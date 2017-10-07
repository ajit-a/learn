#include<stdio.h>
#include <string.h>
#define max 100000001

int arr[max];
void genprime()
{
	long long i,j;
	/*memset(arr,0,max);*/
	for(i=2;i<max;i++)
	{
		if(arr[i]==0)
		{
			for(j=i*2;j<max;j+=i)
			{
				arr[j]=1;
			}
		}
	}
}
int main()
{
	int i;
	genprime();
	long long n;
	/*for(i=2;i<max;i++)
	{
		printf("%d\n",arr[i]);
	}*/
	while(1){
	printf("Enter a number to check for prime: ");
	scanf("%lld",&n);
	if(arr[n]==0)printf("It is prime\n");
	else printf("Not a prime\n");
	}
	return 0;
}
