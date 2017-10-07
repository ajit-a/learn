#include<stdio.h>
#include<pthread.h>

void *fun(void*);

int main()
{
	pthread_t threads_ID[10];
	int value=10,i,j;
	void *exit_status;

	for(i=0;i<10;i++)
		pthread_create(&threads_ID[i],NULL,fun,&threads_ID);
	//for(j=0;j<10;j++)	
		pthread_join(threads_ID,&exit_status);
	return 0;
}
void *fun(void *arg)
{
	int *inc=(int *)arg;
	printf("Thread started value is %u\n",*inc);
	return NULL;
}
