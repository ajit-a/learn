#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>

using namespace std;
#define MAX_TEXT 2048
#define MAX_PAYLOAD 409600

class spMimeCreate
{
	private:
		string spStartB;
		string spSecStart;
		char *spendMsg;
		int sd;
		char message[MAX_TEXT];
		char imessage[MAX_PAYLOAD];
		string spHeader;
	public:
		spMimeCreate();
		~spMimeCreate();
		int spImageAttach();
		void spTextcreate();		
		int spCreateHeader();
		int spCreateConnection(struct sockaddr_in *);
		void spCloseConnection();
		void spWrite();
		void spReadSocket();
		void spWriteSocket(const char *);
};


spMimeCreate::spMimeCreate()
{
	time_t now;
	long long spNum=time(&now);
	char _spNum[20]={0};
	int i=0;
	sprintf(_spNum,"%d",spNum);
	spStartB="------";
	spStartB = spStartB + _spNum;
	spSecStart="--";
	spSecStart=spSecStart+spStartB;
	//cout<<spStartB<<endl;
	sd=0;
	spHeader="Content-Type : ";
	spendMsg="\n.\n";
}

spMimeCreate::~spMimeCreate()
{
}

void spMimeCreate::spTextcreate()
{
	const char *ContentType="Content-Type : text/plain";
	const char *ContentTransferEncoding="Content-Transfer-Encoding : quoted-printable";
	const char *ContentDisposition = "Content-Disposition : quoted-printable";
	//message="Hello, This is message body !!!";
	sprintf(message,ContentType);
	sprintf(message+strlen(message),";");	
	sprintf(message+strlen(message),"\n");	
	sprintf(message+strlen(message),ContentDisposition);
	sprintf(message+strlen(message),"\n\n");	
	sprintf(message+strlen(message),"Hello, This is the message body\n");
	//cout<<message<<endl;
}
int spMimeCreate::spImageAttach()
{
        const char *ContentType="Content-Type : image/jpeg";
        const char *ContentDisposition="Content-Disposition : attachment";
        const char *ContentTransferEncoding="Content-Transfer-Encoding : base64";
	char buf[1024]={0};

	string fPath="";
	string fName="logo.jpg";
	string fPN=fPath+fName;
	string _message="";
	

	sprintf(imessage,ContentType);
	sprintf(imessage+strlen(imessage),";");	

	sprintf(imessage+strlen(imessage),"name = \"");	
	sprintf(imessage+strlen(imessage),fName.data());	
	sprintf(imessage+strlen(imessage),"\"");	
	sprintf(imessage+strlen(imessage),"\n");	

	sprintf(imessage+strlen(imessage),ContentTransferEncoding);
	sprintf(imessage+strlen(imessage),"\n");	

	sprintf(imessage+strlen(imessage),ContentDisposition);
	sprintf(imessage+strlen(imessage),";");	
	sprintf(imessage+strlen(imessage),"filename = \"");	
	sprintf(imessage+strlen(imessage),fPN.data());	
	sprintf(imessage+strlen(imessage),"\"");	
	sprintf(imessage+strlen(imessage),"\n\n");	


	FILE *fp;
	if((fp=popen("/usr/bin/base64 logo.jpg","r"))==NULL)
	{
		cout<<"Unable to open base64"<<endl;
		return 1;
	}
	while(fgets(buf,sizeof(buf),fp)!=NULL)
	{
		_message=_message+buf;
	}
	
	sprintf(imessage+strlen(imessage),_message.data());	
	//cout<<imessage<<endl;
}

int spMimeCreate::spCreateHeader()
{
        const char *ContentType="multipart/mixed";
	string boundary="boundary = \"";
	boundary=boundary+spStartB;
	boundary=boundary + "\"";

	spHeader=spHeader+ContentType;
	spHeader=spHeader+";";
	spHeader=spHeader + boundary;
	cout<<spHeader<<endl;
}
int spMimeCreate::spCreateConnection(struct sockaddr_in *mailS)
{
        sd=socket(AF_INET,SOCK_STREAM,0);
        if(sd == -1)
        {
                printf("Unable to open socket\n");
                return 1;
        }
        if(connect(sd,(struct sockaddr *)mailS,sizeof(*mailS)) == -1)
        {
                printf("Unable to connect");
                return 1;
        }
	/*int len=0;
	sleep(1);
	ioctl(sd,FIONREAD,&len);
	char buffer[2048]={0};
	if(len>0)
		read(sd,buffer,sizeof(buffer));
	cout<<buffer;*/
	return 0;
}
void spMimeCreate::spCloseConnection()
{
        close(sd);
}
void spMimeCreate::spWrite()
{

	string fbuf="MAIL FROM: ajit";
	string tbuf="RCPT TO: chaitanya@tethys.vegayan";
	string dbuf="data";
	string NL="\r\n";
	
	//write(spMimeCreate::sd,fbuf.data(),fbuf.length());
	spMimeCreate::spWriteSocket(fbuf.data());
	write(sd,"\r\n ",sizeof("\r\n"));
	spMimeCreate::spReadSocket();

	write(sd,"VRFY chaitanya@tethys.vegayan ",sizeof("VRFY chaitanya@tethys.vegayan"));
	write(sd,"\r\n ",sizeof("\r\n"));
	spMimeCreate::spReadSocket();

	//write(spMimeCreate::sd,tbuf.data(),tbuf.length());
	spMimeCreate::spWriteSocket(tbuf.data());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
	
	spMimeCreate::spWriteSocket(dbuf.data());
	spMimeCreate::spWriteSocket(NL.data());
	//write(sd,"\r\n",sizeof("\r\n"));
	spMimeCreate::spReadSocket();

	spMimeCreate::spWriteSocket(spHeader.data());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	write(sd,spSecStart.data(),spSecStart.length());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
	

	write(spMimeCreate::sd,message,strlen(message));
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	write(sd,spSecStart.data(),spSecStart.length());
	spMimeCreate::spWriteSocket(NL.data());
	//spMimeCreate::spReadSocket();
	
	write(spMimeCreate::sd,imessage,strlen(imessage)); /* Attach mage */
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	write(sd,spSecStart.data(),spSecStart.length());
	spMimeCreate::spWriteSocket(NL.data());

	write(sd,spendMsg,strlen(spendMsg));
	spMimeCreate::spReadSocket();

	write(sd,"quit ",sizeof("quit"));
	write(sd,"\r\n ",sizeof("\r\n"));
	spMimeCreate::spReadSocket();
	
}
void spMimeCreate::spWriteSocket(const char *s)
{
	write(sd,s,strlen(s));
}
void spMimeCreate::spReadSocket()
{
	
	int len=0;
	char buffer[2048]={0};
	//sleep(1);
	ioctl(sd,FIONREAD,&len);
	if(len>0)
	{
		read(sd,buffer,len);
		//cout<<len<<endl;
	}
	cout<<buffer;
}
int main()
{
	spMimeCreate s;
	struct sockaddr_in mailServer;
	memset((char *)&mailServer,0,sizeof(mailServer));
        mailServer.sin_addr.s_addr=inet_addr("192.168.1.4");
        mailServer.sin_port=htons(25);
        mailServer.sin_family=AF_INET;

	s.spCreateConnection(&mailServer);	
	s.spCreateHeader();
	s.spTextcreate();
	s.spImageAttach();
	s.spWrite();
	s.spCloseConnection();
}
