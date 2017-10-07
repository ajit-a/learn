#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include "spSendMail.h"

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		cout<<"Usage : ./"<<argv[0]<<" Path/ file_name"<<endl;
		return 1;
	}	
	spMimeCreate s;
	struct sockaddr_in mailServer;
	memset((char *)&mailServer,0,sizeof(mailServer));
        mailServer.sin_addr.s_addr=inet_addr("192.168.1.4");
        mailServer.sin_port=htons(25);
        mailServer.sin_family=AF_INET;

	s.spCreateConnection(&mailServer);	
	s.spCreateHeader();
	s.spTextcreate();
	if(s.spImageAttach(string(argv[1]),string(argv[2]))==1)exit(0);
	//s.spZipAttach("/home/ajit/","testsmtp.zip");
	s.spWrite();
	s.spCloseConnection();
}
