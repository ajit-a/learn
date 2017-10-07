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
/*This process is expected to send numbers for addition using pipes to its child process and child will return the sum*/
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
	int c_fd[2];
	int s_fd[2];

	if(pipe(c_fd) != 0)
	{
		printf("Error creating client pipe\n");
		return 0;
	}
	if(pipe(s_fd) != 0)
	{
		printf("Error creating server pipe\n");
		return 0;
	}
	
	if(fork()==0)
	{
		close(s_fd[1]); //close the server write descriptor as client can only read
		close(c_fd[0]); //close the client read descriptor as client will on write on it
		printf("I am child, pid is %d and ppid is %d\n",getpid(),getppid());
		int bytes = read(s_fd[0],&m,sizeof(m));
		if(bytes>0)
		{
			int sum=m.x+m.y+m.z;
			printf("sum is %d\n",sum);
			write(c_fd[1],&sum,sizeof(sum));
		}
	}
	else
	{
		close(s_fd[0]); //close the read descriptor of server as its only going to write. Read from client desc.
		close(c_fd[1]);
		printf("I am parent, pid is %d and ppid is %d\n",getpid(),getppid());
		printf("Enter three numbers\n");
		scanf("%d %d %d",&n.x,&n.y,&n.z);
		write(s_fd[1],&n,sizeof(nums));
	#if 1 //This is the reason why we need two pipes for both way communication, best seen with 2 variables in struct
		int o;
		int bytes = read(c_fd[0],&o,sizeof(o));
		if(bytes>0)
		{
			printf("sum is %d\n",o);
		}
	#endif
	}
	return 0;	
}
