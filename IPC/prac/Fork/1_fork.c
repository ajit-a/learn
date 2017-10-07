/*http://moss.cs.iit.edu/cs351/assets/slides-processmgmt-1.pdf*/
#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t id;
	id=fork();
	if(id==0)
	{
		printf("This is child with pid:%d and ppid:%d\n",getpid(),getppid());
		//exit(0);
	}
	else
	{
		printf("This is parent with pid:%d and ppid:%d\n",getpid(),getppid());
		sleep(10); //Either that exit or this sleep creates a zombie process because child finishes before parent
		//child becomes zombie beause the entry remains in process table and pid cannot be used again.
		//This is handled in 2 ways, either use wait in parent or handle SIGCHLD signal
		//If there is no wait in parent then init takes over that zombie after the parent terminates and performs a wait to remove it.
	}
	printf("Exiting pid:%d and ppid:%d\n",getpid(),getppid());
	wait();	
	//exit(0);
	return 0;
}

