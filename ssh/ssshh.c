#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
	unsigned long hostaddr;
	char *hostaddr_c;
	char *username;
	char *password;
	
	//hostaddr = inet_addr(argv[1]);
	hostaddr_c = (char*)malloc(20);
	hostaddr_c = (argv[1]);
	username = (char*)malloc(10);
	username = argv[2];
	password = (char*)malloc(10);
	password = argv[3];

	char command[50];
	snprintf(command,"%c","ssh",strlen("ssh"));	
	snprintf(command+strlen(command) , "%c", " ", 1);
	snprintf(command+strlen(command) ,"%c", username, strlen(username));
	snprintf(command+strlen(command) , "%c", "@", 1);
	snprintf(command+strlen(command),"%c",hostaddr_c,strlen(hostaddr_c));
	snprintf(command+strlen(command) , "%c", "<", 1);
	snprintf(command+strlen(command) ,"%c", password, strlen(password));
	snprintf(command+strlen(command) , "%c", "\0", 1);
	printf("%s\n",command);
	system(command);
	return 0;
}
