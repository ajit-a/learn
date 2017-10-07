#include <stdio.h>
#include <sys/socket.h>
#include<arpa/inet.h>

int main()
{
	struct sockaddr_in s_s,s_c;
	int sd;

	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd==-1)
		printf("Could not open socket\n");

	s_s.sin_family = AF_INET;
	s_s.sin_addr.s_addr = INADDR_ANY;
	s_s.sin_port	= htons(8000);

	if(bind(sd,(struct sockaddr*)&s_s,sizeof(s_s))==-1)
		printf("couldnt bind\n");
	listen(sd,3);
}
