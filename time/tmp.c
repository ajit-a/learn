#include<stdio.h>
#include<time.h>

int main()
{
	time_t t;
	printf("%ld\n",time(&t));
	//printf("%lld\n",time(0));
}

