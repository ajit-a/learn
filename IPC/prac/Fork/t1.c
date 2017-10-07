#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);
		close(1);
		dup(fd[1]);
                /* Send "string" through the output side of pipe */
		execlp("/usr/bin/ls","ls",NULL);
                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);
		close(0);
		dup(fd[0]);
                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
        
        return(0);
}
