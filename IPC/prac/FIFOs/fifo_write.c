/*
Named pipes (FIFOs)
-------------------
Similar to pipes, but allows for communication between unrelated processes.
This is done by naming the communication channel and making it permanent.

Like pipe, FIFO is the unidirectional data stream.

FIFO creation:

int mkfifo ( const char *pathname, mode_t mode );
 - makes a FIFO special file with name pathname. 
   (mode specifies the FIFO's permissions, as common in UNIX-like 
    file systems).  
 - A FIFO special file is similar to a pipe, except that it is created in 
   a different way. Instead of being an anonymous communications channel,
   a FIFO special file is entered into the file system by calling mkfifo()

Once a FIFO special file has been created, any process can open it
for reading or writing, in the same way as an ordinary file.

Note: Opening a FIFO for reading normally blocks until some other process
      opens the same FIFO for writing, and vice versa.
*/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char buff[100];
	char *mypipe="/tmp/MyPipe";
	
	if(mkfifo(mypipe,0666)!=0)
	{
		perror("Error : ");
	}
	
	int fd;
	fd=open(mypipe,O_WRONLY);
	while(fgets(buff,sizeof(buff),stdin)!=0)
	{
		int len=strlen(buff);
		buff[len-1]='\0';
		write(fd,buff,strlen(buff));	
		break;
	}
	close(fd);
	//unlink(mypipe);
}

