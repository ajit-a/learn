#include<stdio.h>
//#include<sys/time.h>
#include<time.h>

#define EXEC_TIME 19*60*60

int main(int argc,char *argv[])
{
	time_t t;
	int CURR_TIME;
	struct tm *new;
	/*if(argc!=2)
	{
		printf("Usage ./time function\n");
		return 1;
	}*/
	while(1)
	{
		time(&t); 
		new=localtime(&t);
	
		CURR_TIME=new->tm_hour*3600+new->tm_min*60+new->tm_sec;
		if(CURR_TIME==EXEC_TIME)
		{
			printf("Execute function");
		}
		else
		{
			if(CURR_TIME<EXEC_TIME)
			{
				printf("Waiting for %d seconds\n",abs(EXEC_TIME-CURR_TIME));
				sleep(abs(EXEC_TIME-CURR_TIME));
			}
			else
			{
				CURR_TIME=86400-(CURR_TIME-EXEC_TIME);
				printf("Waiting for %d seconds\n",CURR_TIME);
				sleep(CURR_TIME);
			}
		}
	}
}
