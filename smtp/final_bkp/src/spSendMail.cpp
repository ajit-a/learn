#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include "spSendMail.h"

using namespace std;

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
	sd=0;
	spHeader="Content-Type : ";
	spendMsg="\n.\n";
}

spMimeCreate::~spMimeCreate()
{
}

void spMimeCreate::spTextcreate()
{
	/*ContentType="Content-Type : text/plain";
	ContentTransferEncoding="Content-Transfer-Encoding : quoted-printable";
	ContentDisposition = "Content-Disposition : quoted-printable";
	sprintf(message,ContentType);
	sprintf(message+strlen(message),";");	
	sprintf(message+strlen(message),"\n");	
	sprintf(message+strlen(message),ContentDisposition);
	sprintf(message+strlen(message),"\n\n");	*/
	spMimeCreate::spMimeCreateHeader("text/plain");
	sprintf(message+strlen(message),"Hello, This is the message body\n");
}

int spMimeCreate::spImageAttach(string fPath,string fName)
{
	char buf[1024]={0};
	spMimeCreate::spMimeCreateHeader("image/jpeg");
        /*ContentType="Content-Type : image/jpeg";
        ContentDisposition="Content-Disposition : attachment";
        ContentTransferEncoding="Content-Transfer-Encoding : base64";

	sprintf(imessage,ContentType);
	sprintf(imessage+strlen(imessage),";");	
	*/
	sprintf(imessage+strlen(imessage),"name = \"");	
	sprintf(imessage+strlen(imessage),fName.data());	
	sprintf(imessage+strlen(imessage),"\"");	
	sprintf(imessage+strlen(imessage),"\n");	

	sprintf(imessage+strlen(imessage),ContentTransferEncoding);
	sprintf(imessage+strlen(imessage),"\n");	

	sprintf(imessage+strlen(imessage),ContentDisposition);
	sprintf(imessage+strlen(imessage),";");	
	sprintf(imessage+strlen(imessage),"filename = \"");	
	sprintf(imessage+strlen(imessage),fName.data());	
	sprintf(imessage+strlen(imessage),"\"");	
	sprintf(imessage+strlen(imessage),"\n\n");	

	string fPN=fPath+fName;
	string _message="";
	string _popComm="/usr/bin/base64";
	
	_popComm=_popComm+" ";
	_popComm=_popComm+fPN;

	FILE *fp;
	//if((fp=popen("/usr/bin/base64 ../img/logo.jpg","r"))==NULL)
	if((fp=popen(_popComm.data(),"r"))==NULL)
	{
		cout<<"Unable to open base64 at /usr/bin/ "<<endl;
		return 1;
	}
	while(fgets(buf,sizeof(buf),fp)!=NULL)
	{
		_message=_message+buf;
	}
	pclose(fp);
	
	sprintf(imessage+strlen(imessage),_message.data());	
}

int spMimeCreate::spCreateHeader()
{
        ContentType="multipart/mixed";
	string boundary="boundary = \"";
	boundary=boundary+spStartB;
	boundary=boundary + "\"";

	spHeader=spHeader+ContentType;
	spHeader=spHeader+";";
	spHeader=spHeader + boundary;
	//cout<<spHeader<<endl;
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
	return 0;
}
void spMimeCreate::spCloseConnection()
{
        close(sd);
}
void spMimeCreate::spWrite()
{

	string fbuf="MAIL FROM: <ajit>";
	string tbuf="RCPT TO: <chaitanya@tethys.vegayan>";
	string dbuf="data";
	string NL="\r\n";
	
	spMimeCreate::spWriteSocket(fbuf.data());
	write(sd,"\r\n ",sizeof("\r\n"));
	spMimeCreate::spReadSocket();

	write(sd,"VRFY chaitanya@tethys.vegayan ",sizeof("VRFY chaitanya@tethys.vegayan"));
	write(sd,"\r\n ",sizeof("\r\n"));
	spMimeCreate::spReadSocket();

	spMimeCreate::spWriteSocket(tbuf.data());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
	
	spMimeCreate::spWriteSocket(dbuf.data());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	spMimeCreate::spWriteSocket(spHeader.data());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	write(sd,spSecStart.data(),spSecStart.length());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
	

	write(spMimeCreate::sd,message,strlen(message)); /* Text Message */
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	write(sd,spSecStart.data(),spSecStart.length());
	spMimeCreate::spWriteSocket(NL.data());
		
	write(spMimeCreate::sd,imessage,strlen(imessage)); /* Attach mage */
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	write(sd,spSecStart.data(),spSecStart.length());
	spMimeCreate::spWriteSocket(NL.data());

	write(spMimeCreate::sd,zmessage,strlen(zmessage)); /* Attach zip */
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	write(sd,spSecStart.data(),spSecStart.length());
	spMimeCreate::spWriteSocket(NL.data());

	write(sd,spendMsg,strlen(spendMsg));
	spMimeCreate::spReadSocket();

	write(sd,"quit ",sizeof("quit"));
	write(sd,"\r\n ",sizeof("\r\n"));sleep(1);
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
		read(sd,buffer,len);

	cout<<buffer;
}

void spMimeCreate::spMimeCreateHeader(string spType)
{
	if(spType=="text/plain")
	{
		ContentType="Content-Type : text/plain";
		ContentTransferEncoding="Content-Transfer-Encoding : quoted-printable";
		ContentDisposition = "Content-Disposition : quoted-printable";
		sprintf(message,ContentType);
		sprintf(message+strlen(message),";");	
		sprintf(message+strlen(message),"\n");	
		sprintf(message+strlen(message),ContentDisposition);
		sprintf(message+strlen(message),"\n\n");	
	}
	if(spType=="image/jpeg")
	{
        	ContentType="Content-Type : image/jpeg";
	        ContentDisposition="Content-Disposition : attachment";
        	ContentTransferEncoding="Content-Transfer-Encoding : base64";

		sprintf(imessage,ContentType);
		sprintf(imessage+strlen(imessage),";");	
	}
	if(spType=="application/zip")
	{
		ContentType="Content-Type : application/zip";
                ContentDisposition="Content-Disposition : attachment";
                ContentTransferEncoding="Content-Transfer-Encoding : base64";
 
                sprintf(zmessage,ContentType);
                sprintf(zmessage+strlen(zmessage),";");
	}	
}
int spMimeCreate::spZipAttach(string fPath,string fName)
{
	char buf[1024];
	spMimeCreate::spMimeCreateHeader("application/zip");

	sprintf(zmessage+strlen(zmessage),"name = \"");	
	sprintf(zmessage+strlen(zmessage),fName.data());	
	sprintf(zmessage+strlen(zmessage),"\"");	
	sprintf(zmessage+strlen(zmessage),"\n");	

	sprintf(zmessage+strlen(zmessage),ContentTransferEncoding);
	sprintf(zmessage+strlen(zmessage),"\n");	

	sprintf(zmessage+strlen(zmessage),ContentDisposition);
	sprintf(zmessage+strlen(zmessage),";");	
	sprintf(zmessage+strlen(zmessage),"filename = \"");	
	sprintf(zmessage+strlen(zmessage),fName.data());	
	sprintf(zmessage+strlen(zmessage),"\"");	
	sprintf(zmessage+strlen(zmessage),"\n\n");	

	string fPN=fPath+fName;
	string _message="";
	string _popComm="/usr/bin/base64";
	
	_popComm=_popComm+" ";
	_popComm=_popComm+fPN;

	FILE *fp;
	//if((fp=popen("/usr/bin/base64 ../img/logo.jpg","r"))==NULL)
	if((fp=popen(_popComm.data(),"r"))==NULL)
	{
		cout<<"Unable to open base64 at /usr/bin/ "<<endl;
		return 1;
	}
	while(fgets(buf,sizeof(buf),fp)!=NULL)
	{
		_message=_message+buf;
	}
	pclose(fp);
	
	sprintf(zmessage+strlen(zmessage),_message.data());	
	cout<<zmessage<<endl;
	
}
