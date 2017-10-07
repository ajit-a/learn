#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#include "spSendMail.h"

/*int main(int argc,char *argv[])
{
	if(argc!=4)
	{
		cout<<"Usage : ./"<<argv[0]<<" Path/ file_name file_type"<<endl;
		return 1;
	}	
	spMimeCreate s;

	//s.spCreateConnection(&mailServer);	
	s.spCreateHeader();
	s.spWrite();
	s.spTextcreate();
	if(s.spImageAttach(string(argv[1]),string(argv[2]),string(argv[3]))==1)exit(0);
	s.spTerminate();
	//s.spZipAttach("/home/ajit/","testsmtp.zip");
	s.spCloseConnection();
}*/
void spMimeCreate::spMimein(stFPLTrapDetailsList* objstFPLTrapDetailsList)
{
	unsigned int i = 0;
        if( objstFPLTrapDetailsList->iNoOfEntries <= 0 ) { return; }
	spLogDebug("spMimeCreate::spSendTraptoEmail \n");
	
	for (i = 0; i < objstFPLTrapDetailsList->iNoOfEntries; i++)
    	{
		if(objstFPLTrapDetailsList->objstTrapDetails[i].eTrapType == TrapAuthFail || \
                	objstFPLTrapDetailsList->objstTrapDetails[i].eTrapType == TrapMisc || \
	                objstFPLTrapDetailsList->objstTrapDetails[i].eTrapType == TrapSysLog || \
        	        objstFPLTrapDetailsList->objstTrapDetails[i].eTrapType == TrapRttMon)
        	{
                	continue;
        	}
		/*Check for critical traps and call the method with respective parameters */
		cout<<"call received"<<endl;
	}
}

