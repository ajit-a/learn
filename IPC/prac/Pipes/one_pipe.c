/*
 Pipes
-----
 A pipe allows for data flow in one direction; when bidirectional communication
 is needed, two pipes need to be created.

 Only related processes (those in the same branch of the process tree) can
 communicate through a pipe.

 The pipe is created by system call pipe():

 int pipe(int filedes[2]);
  - creates  a  pair  of file descriptors, pointing to a
    pipe inode, and places them in the  array  pointed  to  by
    filedes.   filedes[0]  is  for  reading, filedes[1] is for
    writing.

 Note: When forking processes, the child process inherits descriptors of all 
       files opened (or inherited) by it's parent. 
       (if not explicitly specified otherwise).

 Note: Description of stdin and stdout redirection mechanism  
       (i.e., how the shell connects two unrelated processes by pipe)

 Note: if the process tries to write to the pipe and the reader
       has already closed it's end of the pipe, the writer will receive
       SIGPIPE signal. 

 Note: pipe (and FIFO) can be put to nonblocking mode, so that functions
       like read() do not wait until data are available, but returns an error 
       code if data are not available yet.

Note: Name spaces
-----------------
- FIFOs, shared memory segments and semaphores are identified by key
  (key_t type = integer)
- there exist a mechanism which allows to map the path to an existing
  file to a value of a key; that way, two processes can generate the
  the same key value from a given file

The function used to map pathname (and "project #" to a key:
 key_t ftok ( char *pathname, char proj );

  Common technical implementation of key value evaluation:
   - combines i-node of the file, minor dev # of the volume the file 
     is stored on + the additional 8-bit number (proj)

 Note: the file mustn't be deleted and created again between calls to ftok(),
       since it would be given a different inode number
 Note: the computation neglects major device #, so there is a small chance
       to generate the same key for different pathnames.
*/
/*This process is expected to send 2 numbers for addition using pipes to its child process*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct nums
{
	int x;
	int y;
	int z;
}nums;
int main()
{
	nums n,m;
	int fd[2];

	if(pipe(fd) != 0)
	{
		printf("Error creating pipe\n");
		return 0;
	}
	
	if(fork()==0)
	{
		close(fd[1]); //close the write descriptor as client can only read
		printf("I am child, pid is %d and ppid is %d\n",getpid(),getppid());
		int bytes = read(fd[0],&m,sizeof(m));
		if(bytes>0)
		{
			int sum=m.x+m.y+m.z;
			printf("sum is %d\n",sum);
			//write(fd[1],&sum,sizeof(sum));
		}
	}
	else
	{
		close(fd[0]); //close the read descriptor as server can only write
		printf("I am parent, pid is %d and ppid is %d\n",getpid(),getppid());
		printf("Enter three numbers\n");
		scanf("%d %d %d",&n.x,&n.y,&n.z);
		write(fd[1],&n,sizeof(nums));
	#if 0 //This is the reason why we need to pipes for both way communication, best seen with 2 variables in struct
		int o;
		int bytes = read(fd[0],&o,sizeof(o));
		if(bytes>0)
		{
			printf("sum is %d\n",o);
		}
	#endif
	}
	return 0;	
}
