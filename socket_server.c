#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
int main()
{
	int s_sd,c_sd,sock;
	struct sockaddr_in saddr,caddr;

	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;
	saddr.sin_port=htons(1234);
	sock=socket(AF_INET,SOCK_STREAM,0);

	bind(sock,(struct sockaddr*)&saddr,sizeof(struct sockaddr));
	listen(sock,3);
	int len=sizeof(struct sockaddr_in);
	c_sd=accept(s_sd,(struct sockaddr_in*)&caddr,(socklen_t*)&len);
	read();
	
}
