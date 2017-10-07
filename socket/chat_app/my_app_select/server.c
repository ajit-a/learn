/*
 * However, you can either listen to both of them, or use AF_INET6 instead of AF_UNSPEC. Then you can do setsockopt to disable IPV6_V6ONLY
 */
/*
 * https://banu.com/blog/2/how-to-use-epoll-a-complete-example-in-c/
 * http://www.tenouk.com/Module41.html
 * http://developerweb.net/viewtopic.php?id=2933
 */
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h> /*getaddrinfo*/
#include <sys/types.h> /*struct addrinfo*/

#define SERVERIP be:d1:9f:fd:cf:84
#define SERVERPORT "8080"
#define DEFUNAME "Anonymus"
#define MAXCONN 3
#define MAXBUFF 256

typedef struct client
{
	char *uname;
	char *ip;
	unsigned int sd;
}clientd;
typedef struct clientList
{
	int size;
	clientd *head;
	clientd *tail;
}cList;
void* client_handler(void* cin)
{
	clientd *c=(clientd*)cin;
	char buff[MAXBUFF];
	unsigned int bytes=0,sd=c->sd;
	printf("Thread created for socket:%u\n",sd);
	fflush(0);
	while(1)
	{
		memset(buff,0,sizeof(buff));
		bytes=0;
		bytes = read(sd,buff,MAXBUFF);
		int i=0;
		while(i<bytes)
			printf("%c",buff[i++]);
		fflush(0);
	}
	free(cin);
}
static int create_and_bind()
{
	struct addrinfo hints,*serverinfo,*itr;
	int s,sfd;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_INET6; /*AF_INET or AF_UNSPEC*/
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; /*All interfaces*/

	s=getaddrinfo(NULL,SERVERPORT,&hints,&serverinfo); /*Port should be char*/
	if(s!=0)
	{
		perror("addrinfo ");
		return -1;
	}
	for(itr=serverinfo;itr != NULL ;itr=itr->ai_next)
	{
		sfd = socket(itr->ai_family, itr->ai_socktype, itr->ai_protocol);
		int enable = 1;
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
			error("setsockopt(SO_REUSEADDR) failed");
		if(sfd==-1)
			continue;
		s=bind(sfd,itr->ai_addr,itr->ai_addrlen);
		if(s==0)
			break;
		close(sfd);
	}
	if(itr==NULL)
	{
		printf("Could not bind\n");
		return -1;
	}
	freeaddrinfo(serverinfo);
	return sfd;
}
int main()
{
	int s_sd,c_sd;
	struct sockaddr_in6 *ssock;
	ssock=(struct sockaddr_in6*)malloc(sizeof(struct sockaddr_in6));

	ssock->sin6_port = htons(SERVERPORT);
	ssock->sin6_addr = in6addr_any;
	ssock->sin6_family = AF_INET6;

	/*if((s_sd=socket(AF_INET6,SOCK_STREAM,0))==-1)
	{
		perror("socket error:");
		return -1;
	}
	if((bind(s_sd,(struct sockaddr*)&ssock,sizeof(struct sockaddr_in6)))==-1)
	{
		printf("Bind : %s\n",strerror(errno));
		return -1;
	}*/
	if((s_sd=create_and_bind())==-1)
	{
		printf("Bind : %s\n",strerror(errno));
		return -1;
	}
	if((listen(s_sd,MAXCONN))==-1)
	{
		perror("Listen error :");
		return -1;
	}
	fd_set rfds,tempfds;
	struct timeval tv;
	int ret,maxfd;
	FD_ZERO(&rfds);
	FD_SET(s_sd,&rfds); /*Add server socke to accept client connections*/
	maxfd=s_sd;
	tv.tv_sec = 1;
	rv.tv_usec = 0;
	while(1)
	{
		retval = select(maxfd+1, &rfds , NULL ,NULL ,&tv);
		if(retval > 0)
		{
			socklen_t _clen=sizeof(struct sockaddr_in6);
			struct sockaddr_in6 csock;/*This should never be a pointer*/
			c_sd=accept(s_sd,(struct sockaddr*)&csock,&_clen);
			if(c_sd!=-1)
			{
				printf("Connection accepted\n");
				clientd *c=NULL;
				c=(clientd*)malloc(sizeof(clientd));		
				c->sd=c_sd;

				pthread_t id;
				pthread_create(&id,NULL,client_handler,c);
			}
		}
	}
	return 0;
}
