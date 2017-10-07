#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_KEY 0xABCD
#define SHM_SIZE 5
int main()
{
    int shmid, i;
    char *shm_arr;
	int pid;
    if ((pid = fork()) != 0)
    {
        shmid = shmget (SHM_KEY, SHM_SIZE, IPC_CREAT | 0600);
        shm_arr = shmat (shmid, NULL, 0);
        memset (shm_arr, 0, SHM_SIZE);
        for (i = 0; i < SHM_SIZE; i++)
        {
            shm_arr[i] = i;
        }
        shmdt (shm_arr);
        shmctl (shmid, IPC_RMID, NULL);
    }
    else
    {
        shmid = shmget (SHM_KEY, SHM_SIZE, 0600);
        shm_arr = shmat (shmid, NULL, 0);
        for (i = 0; i < SHM_SIZE; i++)
        {
            printf ("%d ", shm_arr[i]);
        }
        shmdt (shm_arr);
    }
    return 0;
}
