#include<stdio.h>
//#include<sys/time.h>
#include<time.h>

#define EXEC_TIME 19*60*60

int main(int argc,char *argv[])
{
	int t1,t2;
	//struct timeval t1;
	time_t t;
	struct tm *new;
	/*if(argc!=2)
	{
		printf("Usage ./time function\n");
		return 1;
	}*/
	/*if(gettimeofday(&t1,NULL)==0)
	{
		//printf("Time is %f\n",t1.tv_sec);
		//printf("Time is %f\n",t1.tv_usec);
	}*/
	printf("%d seconds elapsed\n",time(&t));
	//time(&t); /*In seconds*/
	new=localtime(&t);/*convert into structure tm*/
	printf("The current date and time are %s",asctime(new));/*print locatime as string */
	//t1=time(&t)/3600;
	//t2=time(&t)%3600;
	//printf("time elasped is %d.%d\n",t1,t2);
	printf("Seconds are %d\n",new->tm_sec);
	printf("Min are %d\n",new->tm_min);
	printf("Hours are %d\n",new->tm_hour);
	printf("Day is %d\n",new->tm_mday);


}
