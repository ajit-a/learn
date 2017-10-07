#include<stdio.h>
#include<sys/time.h>

int main()
{
	fd_set rfds;
	struct timeval tv;
	int retval;

	FD_ZERO(&rfds);
	FD_SET(0,&rfds);

	tv.tv_sec=5;
	tv.tv_usec=0;

	retval = select(1, &rfds , NULL ,NULL ,&tv);

	if(retval == -1)
	{
		perror("select() :");
	}
	else if(retval)
	{
		printf("Data is available now\n");
		if(FD_ISSET(0,&rfds))
			printf("isiset 0 is true\n");
		if(FD_ISSET(1,&rfds))
			printf("isiset 1 is true\n");
	}
	else
	{
		printf("No data in 5 secs\n");
	}
	return 0;
}
