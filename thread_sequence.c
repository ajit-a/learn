#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
void *thread(void *a)
{
	int *j = (int *)a;
	int d = *j;
	printf("Create Thread id :%u\n",pthread_self());
	pthread_mutex_lock(&lock);
	printf("Thread id got access :%u\n",pthread_self());
	printf("Hello\n");
	sleep(1);
	pthread_mutex_unlock(&lock);
	//printf("%d\n",d);
}

int main()
{
	int i;
	pthread_t id;
	for(i=1;i<=5;i++)
	{
		pthread_create(&id,NULL,thread,(void *)&i);
	}
	pthread_join(id,&i);
}
