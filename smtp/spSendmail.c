#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

#define MAILSERVER "192.168.1.4"
#define MAX_BUF 2048
#define MAIL_FROM "MAIL FROM:ajit_ambekar@vegayan.com"
#define Q "QUIT"


int spCreateConnection(struct sockaddr_in *);
int spTalk();
void spCloseConnection();
void spGenerateMsg();
void spMailread();
void spMailwrite();
void spGenerateMailList();
char *sbuf;
char rbuf[MAX_BUF];
int sd;

int main()
{
	struct sockaddr_in mailServer;

	bzero((char *)&mailServer,sizeof(mailServer));

	mailServer.sin_addr.s_addr=inet_addr("192.168.1.4");
	mailServer.sin_port=htons(25);
	mailServer.sin_family=AF_INET;

	spCreateConnection(&mailServer);
	spGenerateMsg();
	spGenerateMailList();
	spTalk();
	spCloseConnection();
	return 0;
}

int spCreateConnection(struct sockaddr_in *mailS)
{
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd == -1)
	{
		printf("Unable to open socket\n");
		return;
	}
	if(connect(sd,(struct sockaddr *)mailS,sizeof(*mailS)) == -1)
	{
		printf("Unable to connect");
		return;
	}
}

void spCloseConnection()
{
	close(sd);
}
void spGenerateMsg()
{
	sbuf=malloc(sizeof(Q));
	sbuf=Q;
	//printf("size of sbuf = %d\n",sizeof(sbuf));
	//printf("%s\n",sbuf);
	//sbuf=MAIL_FROM;
}
void spGenerateMailList()
{
}
int spTalk()
{
	spMailread();
	spMailwrite();
	spMailread();
}
void spMailread()
{
	int len;
	len=read(sd,rbuf,MAX_BUF);
	printf("%s",rbuf);
	memset(rbuf,0,sizeof(rbuf));
}
void spMailwrite()
{
	write(sd,"MAIL FROM: ",sizeof("MAIL FROM:"));
	write(sd,"ajit@tethys.com",sizeof("ajit@tethys.com"));
	write(sd,"\r\n",sizeof("\r\n"));
	//spMailread();
	write(sd,"RCPT TO:",sizeof("RCPT TO:"));
	write(sd,"aji@tethys.vegayan",sizeof("ajit@tethys.vegayan"));
	write(sd,"\r\n",sizeof("\r\n"));
	spMailread();
	//write(sd,sbuf,sizeof(sbuf));
	if(write(sd,"QUIT",4)<0)printf("Write error\n");
	if(write(sd,"\r\n",sizeof("\r\n"))<0)printf("Write error\n");
	//spMailread();
}
