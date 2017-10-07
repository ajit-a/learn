/*
 * pthred_detach only tells the OS to release all the resources.
 * If we want a thread to continue even after completion of main program then the main program should exit using pthread_exit.
*/
#include <pthread.h>
#include <stdio.h>

void *func(void *data)
{
    //while (1)
	int i;
	for(i=0;i<10;i++)
    {
        printf("Speaking from the detached thread...\n");
        sleep(5);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t handle;
    if (!pthread_create(&handle, NULL, func, NULL))
    {
        printf("Thread create successfully !!!\n");
        if ( ! pthread_detach(handle) )
            printf("Thread detached successfully !!!\n");
    }

    sleep(5);
    printf("Main thread dying...\n");
	int ret=0;
	pthread_exit(&ret);
//    return 0;
}
