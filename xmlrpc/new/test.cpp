#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<iostream>
#include<string.h>

//#include<xmlrpc-c/client.hpp>
//#include <xmlrpc-c/client_transport.hpp>
#include<XmlRpcCpp.h>

#include <sys/select.h>
#include<xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_pstream.hpp>

using namespace std;

class Add:public xmlrpc_c::method
{
	Add(){};
	int call_fun()
	{
		return 10;
	}
};

int main()
{
	/*struct sockaddr_in cli,ser;
	int sd,sd_c,c;

	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd==-1)
		cout<<"could not create socket"<<endl;
	
	memset((void*)&cli,0,(sizeof(struct sockaddr_in)));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(5000);
	ser.sin_addr.s_addr=INADDR_ANY;
	
	if(bind(sd,(struct sockaddr *)&ser,sizeof(ser))<0)
		cout<<"Bind error"<<endl;
	cout<<"Bind done"<<endl;

	listen(sd,3);

	cout<<"Waiting for incomming connections"<<endl;
	c=sizeof(struct sockaddr_in);
	
	sd_c=accept(sd,(struct sockaddr *)&cli,(socklen_t*)&c);
	if(sd_c<0)
		cout<<"Connection failed"<<endl;
	cout<<"Connection accepted"<<endl;

	*/
	//ConfigData objConfigData;
	int iStatus  = 0;
	const char *pcMethodName = NULL;
	int iPortNumber = 0;
	int rc = -1,i,ret;
	
	
	xmlrpc_c::registry objRegistry2;
	xmlrpc_c::methodPtr const rpc_method(new Add);

	iPortNumber = 5000;
	objRegistry2.addMethod("call_fun",rpc_method);

	//signal(SIGPIPE,SIG_IGN);

	int eserver_fd = -1;
	eserver_fd = socket(AF_INET, SOCK_STREAM, 0); // create TCP socket
	if (eserver_fd == -1)
	{
		printf("\n socket eserver : ASA\n");
		perror("eserver_fd:");
		abort();
	}
	/* now start to bind the socket */
        struct sockaddr_in name;


	bzero(&name,sizeof(name));

	name.sin_family = AF_INET; /* internet socket */
	name.sin_port   = htons(iPortNumber);

	rc = inet_pton(AF_INET, "127.0.0.1", (void*)&name.sin_addr); /* convert ASCII IP Addr. to integer */
	if(rc <= 0)
	{
		perror("inet_pton EServer error:");
		abort();
	}

		rc = bind(eserver_fd, (struct sockaddr *)&name, sizeof(name)); /* bind to socket */
		if (rc != 0)
		{
			perror("eserver_bind:");
		}


	  for (i = 0; i < 10; i++)
    {
        ret = listen(eserver_fd, 3); /* start listening on eserver port */
        if (ret == 0)
        {
            break;
        }
        perror("listen(eserver_fd error:");
        printf("\n listen(eserver : ASA \n");
    }
    if (ret != 0)
    {
    }

    char* edata;
    /*edata.eserver_fd = eserver_fd; 
    edata.objConfigData = objConfigData;*/
    //*pdata = edata;
	return 0;
}
