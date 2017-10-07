#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int pdf[2];
	char buf[10];

	if(pipe(pdf)==-1)
	{
		perror("Pipe error");
	}
	if(!fork())
	{
		close(1);
		printf("I am child\n");/*Will not print since stdout is closed */
		dup(pdf[1]); /*Duplicates the first availabe File descriptor (1) which is just closed hance ls output goes here insted of stdout*/
		close(pdf[0]);
		//printf("Writing to PIPE\n");
		execlp("ls","ls",NULL);
	}
	else
	{
		printf("I am parent\n");
		close(0);
		dup(pdf[0]);
		close(pdf[1]);
		execlp("wc","wc","-l",NULL);
		wait();
	}
	return 0;
}
