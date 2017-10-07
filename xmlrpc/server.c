#include<stdio.h>
#include<xmlrpc_server.h>
#include<xmlrpc_abyss.h>

static xmlrpc_value * sample_add(xmlrpc_env * const envP,xmlrpc_value * const paramArrayP, void * const serverContext)
{
	xmlrpc_int32 x,y,z;

	xmlrpc_parse_value(envP,paramArrayP,"(ii)",&x,&y);
	if(envP->fault_occurred)
		return NULL;
	
	z=x+y;

	return xmlprc_build_value(envP,"i",z);
}

int main(int argc,const char **argv)
{
	xmlrpc_env env;
	xmlrpc_server_abyss_parms serverparam;
	xmlrpc_registry *registryP;

	xmlrpc_env_init(&env);

	registryP = xmlrpc_registry_new(&env);

	xmlrpc_registry_add_method(&env,registryP,NULL,"sample.add",&sample_add,NULL);

	serverparam.config_file_name = argv[1];
	serverparam.registryP = registryP;

	printf("starting XML-RPC server...\n");

	xmlrpc_abyss(&env,&serverparam,XMLRPC_APSIZE(registryP));
	
	return 0;
}
