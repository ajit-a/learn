#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#include<pthread.h>

void *connection_handler(void *);
void *readFromClient(void *sd);
void *writeToClient(void *sd);

int main(int argc,char * argv[])
{
	int sd,sd_c,c,*new_sock;
	struct sockaddr_in server,client;
	char *message;
	sd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sd==-1)
		printf("Could not create socket\n");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8000);

	if(bind(sd,(struct sockaddr*)&server,sizeof(server))==-1)
		printf("Bind failed\n");
	
	puts("Bind done\n");

	listen(sd,3);

	puts("Waiting for connections\n");

	c=sizeof(struct sockaddr_in);
	while(sd_c=accept(sd,(struct sockaddr*)&client,(socklen_t*)&c))
	{
		if(sd_c==-1)
		{
			puts("Error\n");
		}
		printf("Accepted sd:%d\n",sd_c);
	
		message="Hello";
		write(sd_c,message,strlen(message));
		pthread_t sniffer_thread;
		new_sock=malloc(1);
		*new_sock=sd_c;

		if(pthread_create(&sniffer_thread,NULL,connection_handler,(void*)new_sock)<0)
		{
			perror("Could not create thread\n");
			return 1;
		}
		puts("Handler assigned\n");
		sd_c=0;
	}
	return 0;
}

void *connection_handler(void *sd)
{
	int sock=*(int*)sd;
	int read_size=0;
	char message[2000],client_message[2000];
	printf("Thread with sd:%d\n",sock);
	//message="\nInside connection handler\n";
	/*write(sock,message,strlen(message));

	while((read_size = recv(sock,client_message,2000,0))>0)
	{
		printf("sd:%d :: %s\n",sock,client_message);
		write(sock,message,strlen(message));
		memset(client_message,'\0',sizeof(client_message));
		memset(message,'\0',sizeof(message));
	}
	if(read_size==0)
	{
		puts("Client disconnected\n");
		fflush(stdout);
	}
	else if(read_size==-1)
		perror("Read error\n");
	free(sd);*/
		pthread_t rClient,wClient	;
		if(pthread_create(&rClient,NULL,readFromClient,sd)<0)
		{
			perror("Could not create thread\n");
			return 1;
		}
		if(pthread_create(&wClient,NULL,writeToClient,sd)<0)
		{
			perror("Could not create thread\n");
			return 1;
		}
	
	return 0;
}
void *readFromClient(void *sd)
{
	char client_message[2000];
	int sock=*(int *)sd;
	int read_size=0;
	while((read_size = recv(sock,client_message,2000,0))>0)
        {
                printf("sd:%d :: %s\n",sock,client_message);
                memset(client_message,'\0',sizeof(client_message));
        }
        if(read_size==0)
        {
                puts("Client disconnected\n");
                fflush(stdout);
        }
        else if(read_size==-1)
                perror("Read error\n");
        free(sd);

        return 0;
}
void *writeToClient(void *sd)
{
	char server_message[2000];
	int sock=*(int *)sd;
	while(1)
	{
		scanf("%s",server_message);
		write(sock,server_message,strlen(server_message));
	}
}
