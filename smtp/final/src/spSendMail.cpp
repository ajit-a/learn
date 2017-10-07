#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include "spSendMail.h"
#include <fstream>
using namespace std;

#define UNAME "ajit@tethys.vegayan"
#define PASS "ajit"
#define SMTP_SERVER "192.168.1.4"
#define SMTP_PORT 25


spMimeCreate::spMimeCreate() /* Some basic constants are initialised and boundary variable is generated from time() */
{
	time_t now;
	long long spNum=time(&now);
	char _spNum[20]={0};
	sprintf(_spNum,"%lld",spNum);
	spStartB="------";
	spStartB = spStartB + _spNum;
	spSecStart="--";
	spSecStart=spSecStart+spStartB;
	sd=0;
	spHeader="Content-Type : ";
	spendMsg="\n.\n";
	NL="\r\n";
	
        memset((char *)&mailServer,0,sizeof(mailServer));
        mailServer.sin_addr.s_addr=inet_addr(SMTP_SERVER);
        mailServer.sin_port=htons(SMTP_PORT);
        mailServer.sin_family=AF_INET;
	spCreateConnection(&mailServer);
}

spMimeCreate::~spMimeCreate()
{
}

void spMimeCreate::spTextcreate() /* Generates the text body currently hardcoded*/
{
	spMimeCreate::spMimeCreateHeader("text/plain");
	sprintf(message+strlen(message),spFetchMailBody().data());
	spWriteSocket(message);
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
}
string spMimeCreate::spFetchMailBody()
{
        string body="";
        body=body+"Hello, This is the message body\n";
        return(body);
}
int spMimeCreate::spImageAttach(string fPath,string fName,string type) /* Generates the Image MIME body*/
{
	if(type=="image")
		spMimeCreate::spMimeCreateHeader("image/jpeg");
	else
		if(type=="zip")
			spMimeCreate::spMimeCreateHeader("application/zip");
		else
		{
			printf("Invalid argument %s\n",type.data());
			return 1;
		}
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

	FILE *fp;
	if((fp=fopen(fPN.data(),"r"))==NULL)
	{
		cout<<"Unable to open file "<<fPN<<endl;
		return 1;
	}
	_message=encode(fp,72);
	fclose(fp);
	
	sprintf(imessage+strlen(imessage),_message.data());	
	spWriteSocket(spSecStart.data());
	spMimeCreate::spWriteSocket(NL.data());
	spWriteSocket(imessage);
	spMimeCreate::spWriteSocket(NL.data());
	//spMimeCreate::spReadSocket();
	return 0;
}

void spMimeCreate::spCreateHeader() /* Major header is created */
{
        ContentType="multipart/mixed";
	string boundary="boundary = \"";
	boundary=boundary+spStartB;
	boundary=boundary + "\"";

	spHeader=spHeader+ContentType;
	spHeader=spHeader+";";
	spHeader=spHeader + boundary;
}
int spMimeCreate::spCreateConnection(struct sockaddr_in *mailS) /*opens the socket */
{
        sd=socket(AF_INET,SOCK_STREAM,0);
	//fcntl(sd, F_SETFL, O_NONBLOCK);
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
void spMimeCreate::spCloseConnection() /* Close the socket */
{
        close(sd);
}
void spMimeCreate::spWrite() /* Actual write function, will be modified */
{

	string fbuf="MAIL FROM: <ajit>";
	string tbuf="RCPT TO: <chaitanya@tethys.vegayan>";
	string dbuf="data";
	
	spMimeCreate::spWriteSocket("EHLO localhost"); /* EHLO */
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();

	spMimeCreate::spWriteSocket(fbuf.data());
	write(sd,"\r\n ",sizeof("\r\n"));
	spMimeCreate::spReadSocket();

	write(sd,"VRFY chaitanya@tethys.vegayan ",sizeof("VRFY chaitanya@tethys.vegayan"));
	write(sd,"\r\n ",sizeof("\r\n"));
	spMimeCreate::spReadSocket();

	spMimeCreate::spWriteSocket(tbuf.data());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
	
	//spAuth();
	
	spMimeCreate::spWriteSocket(dbuf.data());
	spMimeCreate::spWriteSocket(NL.data());
	
	spMimeCreate::spWriteSocket("From: Simplus\n");
	spMimeCreate::spWriteSocket("Subject: Trap Alert\n");

	spMimeCreate::spWriteSocket(spHeader.data());
	spMimeCreate::spWriteSocket(NL.data());

	write(sd,spSecStart.data(),spSecStart.length());
	spMimeCreate::spWriteSocket(NL.data());
	
}
void spMimeCreate::spAuth()
{
	ofstream ufile;
	ufile.open(".Suname_");
	ufile << UNAME;
	ufile.close();
	FILE *fp=fopen(".Suname_","r");
	string _uname=encode(fp,72);
	fclose(fp);
	
	ufile.open(".Spass_");
	ufile << PASS;
	ufile.close();
	fp=fopen(".Spass_","r");
	string _pass=encode(fp,72);
	fclose(fp);
	remove(".Suname_");
	remove(".Spass_");
	spMimeCreate::spWriteSocket(_uname.data());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
	spMimeCreate::spWriteSocket(_pass.data());
	spMimeCreate::spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
	exit(0);
}
void spMimeCreate::spTerminate()
{
	spWriteSocket(spendMsg);
	spMimeCreate::spReadSocket();

	spWriteSocket("quit");
	spWriteSocket(NL.data());
	spMimeCreate::spReadSocket();
}
void spMimeCreate::spWriteSocket(const char *s) /*Not yet used, will be used to write from withing the function body after MIME */
{
	write(sd,s,strlen(s));
}
void spMimeCreate::spReadSocket() /* Read the response from server */
{
	
	int len=0;
	char buffer[2048]={0};
	//ioctl(sd,FIONREAD,&len);
		len=read(sd,buffer,2048);
	if(len>0)
	{
		cout<<buffer;
	}
}

void spMimeCreate::spMimeCreateHeader(string spType) /* Creates header depending upon the argunet passed */
{
	if(spType=="text/plain")
	{
		ContentType="Content-Type : text/plain";
		ContentTransferEncoding="Content-Transfer-Encoding : quoted-printable";
		ContentDisposition = "Content-Disposition : quoted-printable";
		string charset="charset: ISO-8859-1";
		sprintf(message,ContentType);
		sprintf(message+strlen(message),";");	
		sprintf(message+strlen(message),charset.data());
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
 
                sprintf(imessage,ContentType);
                sprintf(imessage+strlen(imessage),";");
	}	
}

/*--------------------Code for base64 Encoding from Internet----------------------*/
static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
 *  * ** Translation Table to decode (created by author)
 *   * */
static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

/*
 *  * ** b64_message
 *   * **
 *    * ** Gather text messages in one place.
 *     * **
 *      * */
#define B64_MAX_MESSAGES 7

#define b64_message( ec ) ((ec > 0 && ec < B64_MAX_MESSAGES ) ? b64_msgs[ ec ] : b64_msgs[ 0 ])


void spMimeCreate::encodeblock( unsigned char *in, unsigned char *out, int len )
{
    out[0] = (unsigned char) cb64[ (int)(in[0] >> 2) ];
    out[1] = (unsigned char) cb64[ (int)(((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ (int)(((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6)) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ (int)(in[2] & 0x3f) ] : '=');
}

/*
 *  * ** encode
 *   * **
 *    * ** base64 encode a stream adding padding and line breaks as per spec.
 *     * */
string spMimeCreate::encode( FILE *infile, int linesize )
{
    unsigned char in[3];
        unsigned char out[4];
    int i, len, blocksout = 0;
 char outfile[4096000];
	memset(outfile,0,sizeof(outfile));
int z=0;
        *in = (unsigned char) 0;
        *out = (unsigned char) 0;
    while( feof( infile ) == 0 ) {
        len = 0;
       for( i = 0; i < 3; i++ ) {
            in[i] = (unsigned char) getc( infile );
            if( feof( infile ) == 0 ) {
                len++;
            }
            else {
                in[i] = (unsigned char) 0;
            }
        }
        if( len > 0 ) {
            encodeblock( in, out, len );
            for( i = 0; i < 4; i++ ) {
		outfile[z++]=(out[i]);
		//putc(out[i],stdout);
            }
            blocksout++;
        }
        if( blocksout >= (linesize/4) || feof( infile ) != 0 ) {
            if( blocksout > 0 ) {
		outfile[z++]='\r';
		outfile[z++]='\n';
            }
            blocksout = 0;
        }
    }
    return( outfile );
}

