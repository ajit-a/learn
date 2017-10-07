#include<stdio.h>
#include<xmlrpc.h>
#include<xmlrpc_client.h>

#define VERSION "0.001"
#define NAME "AA"

int main()
{
	xmlrpc_env env;
	xmlrpc_value *result = NULL;

	xmlrpc_client_init(XMLRPC_CLIENT_NO_FLAGS,NAME,VERSION);
	xmlrpc_env_init(&env);
	printf("env is %s\n",env);
}

