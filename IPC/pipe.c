#include<stdio.h>
#include<stdlib.h>

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
		printf("I am child\n");
		printf("Writing to PIPE\n");
		write(pdf[1],"Ajit",5);
		exit(0);
	}
	else
	{
		printf("I am parent\n");
		read(pdf[0],buf,5);
		printf("%s\n",buf);
		printf("Exiting parent\n");
		wait();
	}
	return 0;
}
