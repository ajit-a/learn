/*http://stackoverflow.com/questions/231912/what-is-the-difference-between-sigaction-and-signal
 * It is better to use sigaction rather than signal. But both essentially does the same work
*/
#include <stdio.h>
#include <signal.h>
void int_handler(int sing)
{
	printf("Interrupt recieved\n");
}
int main()
{
	signal(SIGUSR1,int_handler);
	pid_t id;
	id=fork();
	if(id==0)
	{
	}
	else
	{
		kill(id,SIGUSR1);
		raise(SIGUSR1);
	}
	return 0;
}
