#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;
pthread_mutex_t lock;
void *thread(void *a)
{
	int *j = (int *)a;
	int d = *j;
	cout<<"Create Thread id :"<<pthread_self()<<endl;
	pthread_mutex_lock(&lock);
	cout<<"Thread id got access :"<<pthread_self()<<endl;
	printf("Hello\n");
	sleep(1);
	pthread_mutex_unlock(&lock);
	//printf("%d\n",d);
}

int main()
{
	int i;
	pthread_t id;
	for(i=1;i<=8;i++)
	{
		pthread_create(&id,NULL,thread,(void *)&i);
		//sleep(1);
	}
	void *ret;
	pthread_join(id,&ret);
}
