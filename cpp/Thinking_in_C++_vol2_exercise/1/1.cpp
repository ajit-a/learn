#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
#include <csignal>

using namespace std;

extern int errno;

int getErrorCode()
{
	return 10;
}

void setErrNo()
{
	ifstream fp("noFile.dat");
	if(!fp.good())
		return;
}

void handleSignal(int a)
{
	cout<<"Recieved signal SIGUSR1"<<endl;
	return;
}
void genSignal(int a)
{
	if(a==0)
		raise(SIGUSR1);
}
void getException() 
{
	throw 10;
}
void HandleError()
{
	int ret=getErrorCode();
	switch(ret)
	{
		case 1:
			cout<<"Error 1"<<endl;
			break;
		default:
			cout<<"Error No: "<<ret<<endl;
			break;
	}
	setErrNo();
	cout<<"Err no set is :"<<errno<<" "<<strerror(errno)<<endl;

	signal(SIGUSR1,handleSignal);
	genSignal(0);
	try
	{
		getException();
	}
	catch(int &a)
	{
		cout<<"Caught value :"<<a<<endl;
	}
	catch(...)
	{
		cout<<"Caught (...)"<<endl;
	}
}

int main()
{
	HandleError();
}
