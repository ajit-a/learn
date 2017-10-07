#include <stdio.h>
#include <pthread.h>

void* daemon(void *);

void* daemon(void *i)
{
	sleep(10);
}

int main()
{
	pthread_t i;
	pthread_create(&i,NULL,daemon,NULL);
	return 0;
}
