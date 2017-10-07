#include<strings.h>

#ifndef _H_spSendMail
#define _H_spSendMail
#define MAX_TEXT 2048
#define MAX_PAYLOAD 409600

using namespace std;

class spMimeCreate
{
	private:
		string spStartB;
		string spSecStart;
		const char *spendMsg;
		int sd;
		char message[MAX_TEXT];
		char imessage[MAX_PAYLOAD];
		char zmessage[MAX_PAYLOAD];
		string spHeader;
		const char *ContentType;
		const char *ContentTransferEncoding;
		const char *ContentDisposition;
	public:
		spMimeCreate();
		~spMimeCreate();
		int spImageAttach(string,string);
		void spTextcreate();		
		int spCreateHeader();
		int spCreateConnection(struct sockaddr_in *);
		void spCloseConnection();
		void spWrite();
		void spReadSocket();
		void spWriteSocket(const char *);
		void spMimeCreateHeader(string);
		int spZipAttach(string ,string);
};

#endif
