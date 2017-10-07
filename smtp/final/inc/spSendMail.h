#include<strings.h>
#include "spGUIMediatorCommon.h"

#ifndef _H_spSendMail
#define _H_spSendMail
#define MAX_TEXT 2048
#define MAX_PAYLOAD 4096000

using namespace std;

class spMimeCreate
{
	private:
		string spStartB;
		string spSecStart;
		string NL;
		const char *spendMsg;
		int sd;
		char message[MAX_TEXT];
		char imessage[MAX_PAYLOAD];
		string spHeader;
		const char *ContentType;
		const char *ContentTransferEncoding;
		const char *ContentDisposition;
		struct sockaddr_in mailServer;
	public:
		spMimeCreate();
		int spCreateConnection(struct sockaddr_in *);
		void spCreateHeader();
		void spWrite();
		void spMimeCreateHeader(string);
		void spTextcreate();		
		int spImageAttach(string,string,string);
		void spTerminate();
		void spCloseConnection();
		~spMimeCreate();
		void spReadSocket();
		void spWriteSocket(const char *);
		string encode( FILE *, int);
		void encodeblock( unsigned char *, unsigned char *, int);
		void spAuth();
		string spFetchMailBody();

		void spMimein(stFPLTrapDetailsList*);
};

#endif
