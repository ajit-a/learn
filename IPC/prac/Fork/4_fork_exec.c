/*http://moss.cs.iit.edu/cs351/assets/slides-processmgmt-1.pdf*/
/*
 * In this program we are taking output from a chlid process to the parent process
 * If we just want to send data manually, it can be done like in t1.c but Sometime we need to redirect output to stdout hence we use
 * dup
*/
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
int main()
{
	pid_t id;
	int fds[2];
	if(pipe(fds)==-1)
	{
		perror("pipe");
		return 1;
	}
	id=fork();
	if(id==0)
	{
		printf("This is child with pid:%d and ppid:%d\n",getpid(),getppid());
		close(fds[0]);//Close stdin as child is only going to write
		close(1);//Close stdout
		dup(fds[1]);//Change stdout to fds out
		execlp("/usr/bin/ls","ls",NULL);//I cannot see the output of this command, so I need pipes to communicate between parent and child
		perror("execl");
		close(fds[1]);
	}
	else
	{
		close(fds[1]);
		close(0);
		dup(fds[0]);
		printf("This is parent with pid:%d and ppid:%d\n",getpid(),getppid());
		char buffer[256];
		while(1)
		{
			int bytes=read(fds[0],buffer,sizeof(buffer));
			if(bytes==-1)
			{	
				if(errno=EINTR)//Interrupt
					continue;
				else
					perror("read");
			}
			else
			if(bytes==0)
				break;
			else
			{
				printf("%s",buffer);
			}
		}
		//sleep(10); //Either that exit or this sleep creates a zombie process because child finishes before parent
		//child becomes zombie beause the entry remains in process table and pid cannot be used again.
		//This is handled in 2 ways, either use wait in parent or handle SIGCHLD signal
		//If there is no wait in parent then init takes over that zombie after the parent terminates and performs a wait to remove it.
	}
	printf("Exiting pid:%d and ppid:%d\n",getpid(),getppid());
	wait();	
	return 0;
}

