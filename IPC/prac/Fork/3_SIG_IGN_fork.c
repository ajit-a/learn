/*line no 22 is changed*/
/*http://moss.cs.iit.edu/cs351/assets/slides-processmgmt-1.pdf*/
/*Why parent exists ?
 * http://stackoverflow.com/questions/14266485/understanding-sigchld-when-the-child-process-terminates*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void clean_up(int signal)
{
	int status;
	wait(&status);//A single wait would club requests from multiple childs if sent together, hence we will require a while loop
	//while( (pid = waitpid(-1,&status, WNOHANG)) > 0 ){};
}
int main()
{
	pid_t id;
	id=fork();

	/**/
	struct sigaction sig_child;
	memset(&sig_child,0,sizeof(struct sigaction));
	sig_child.sa_handler = SIG_IGN; //I am use default (comment this line )sa_handler i.e not create my function then parent sleep but If I use my own function then parent wakes up as soon as clild send a SIGCHLD
	//If I use SIG_ING then child terminates sucessfully and parent also continues to sleep
	//sig_child.sa_flags = SA_NOCLDSTOP; As of this this is not useful. Refer below
	sigaction(SIGCHLD,&sig_child,NULL);

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

/*
 * Can also be done using
 * if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
 *   perror(0);
 *     exit(1);
 *     }
 *     One drawback of this method is that it is slightly less portable than explicitly calling waitpid:
*/
