#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int sd;
	struct sockaddr_in server;
	char message[20000],reply[200000];
	sd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sd==-1)
		printf("Colud not create socket\n");
	else
		printf("Created socket\n");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8000);

	if(connect(sd,(struct sockaddr *)&server,sizeof(server))<0)
	{
		puts("Connect error\n");
		return 1;
	}
	puts("Connected\n");
	
	//message="GET / HTTP/1.1\r\n\r\n";
	sprintf(message,"Hello");
	while(1){
	scanf("%s",message);
	if(send(sd,message,strlen(message),0)<0)
	{
		puts("send Failed\n");
		return 1;
	}
	puts("Data sent\n");
	if(recv(sd,reply,200000,0)<0)
	{
		puts("Recv failed\n");
		return 1;
	}
	puts(reply);
	}
	close(sd);
	return 0;
}
