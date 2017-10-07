#include<iostream>
     #include <sys/types.h>
     #include <sys/socket.h>
     #include <netinet/in.h>
     #include <netdb.h>
     #include <stdio.h>
#include<string.h>
#include<stdlib.h>
     using namespace std;
     #define HELO "HELO 192.168.1.4\r\n"
     #define DATA "DATA\r\n"
     #define QUIT "QUIT\r\n"

    //#define h_addr h_addr_list[0]
    //FILE *fin;
    int sock;
    struct sockaddr_in server;
    struct hostent *hp, *gethostbyname();
    char buf[BUFSIZ+1];
    int len;
    char *host_id="192.168.1.4";
    char *from_id="ajit";
    char *to_id="chaitanya@tethys.vegayan";
    char *sub="testmail\r\n";
    char wkstr[100]="hello how r u\r\n";

    /*=====Send a string to the socket=====*/

    void send_socket(char *s)
    {
	//cout<<s<<"---"<<strlen(s)<<endl;
        write(sock,s,strlen(s));
        write(1,s,strlen(s));
        //printf("Client:%s\n",s);
    }

    //=====Read a string from the socket=====*/

    void read_socket()
    {
        len = read(sock,buf,BUFSIZ);
        write(1,buf,len);
      //printf("Server:%s\n",buf);
    }

    /*=====MAIN=====*/
    int main(int argc, char* argv[])
    {

    /*=====Create Socket=====*/
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock==-1)
    {
     perror("opening stream socket");
     exit(1);
    }
    else
      cout << "socket created\n";
    /*=====Verify host=====*/
    server.sin_family = AF_INET;
    hp = gethostbyname(host_id);
    if (hp==(struct hostent *) 0)
    {
     fprintf(stderr, "%s: unknown host\n", host_id);
     exit(2);
    }

    /*=====Connect to port 25 on remote host=====*/
    memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
    server.sin_port=htons(25); /* SMTP PORT */
    if (connect(sock, (struct sockaddr *) &server, sizeof server)==-1)
    {
     perror("connecting stream socket");
     exit(1);
    }
    else
      cout << "Connected\n";
    /*=====Write some data then read some =====*/
    read_socket(); /* SMTP Server logon string */
    send_socket(HELO); /* introduce ourselves */
    read_socket(); /*Read reply */
    //send_socket("MAIL FROM: "); 
    write(sock,"MAIL FROM: ",sizeof("MAIL FROM:"));
    send_socket(from_id);
    //write(sock,"ajit",sizeof("ajit"));
    send_socket("\r\n");
    read_socket(); /* Sender OK */
    //send_socket("VRFY ");
    //write(sock,"VRFY ",sizeof("VRFY"));
    //write(sock,"ajit",sizeof("ajit"));
	write(sock,"VRFY chaitanya@tethys.vegayan ",sizeof("VRFY chaitanya@tethys.vegayan"));
    //send_socket(from_id);
    send_socket("\r\n");
    read_socket(); // Sender OK */
    send_socket("RCPT TO: "); /*Mail to*/
    //write(sock,"RCPT TO: ",sizeof("RCPT TO: "));
    send_socket(to_id);
    send_socket("\r\n");
    read_socket(); // Recipient OK*/
    send_socket(DATA);// body to follow*/
    send_socket("Subject: ");
    send_socket(sub);
    read_socket(); // Recipient OK*/
    send_socket(wkstr);
    send_socket(".\r\n");
    read_socket(); 
    send_socket(QUIT); /* quit */
    read_socket(); // log off */

    //=====Close socket and finish=====*/
    close(sock);
    exit(0);
  }
