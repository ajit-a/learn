#include <stdio.h>
#include <stdlib.h>
#include <xmlrpc.h>
#include <xmlrpc_client.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/util.h>

#define XMLRPC_NAME       "XML-RPC tesaja"
#define XMLRPC_VERSION    "0.1"

int main()
{
    xmlrpc_env env;
    xmlrpc_value *result = NULL;

    xmlrpc_client_init(XMLRPC_CLIENT_NO_FLAGS, XMLRPC_NAME, XMLRPC_VERSION);
    xmlrpc_env_init(&env);


     result = xmlrpc_client_call(&env, "http://xmlrpc-c.sourceforge.net/api/sample.php" ,
                                 "sample.sumAndDifference", "(ii)", //method
                                (xmlrpc_int32) 5,                  //var
                                (xmlrpc_int32) 3);                 //var

    /* ma code */
     char output[1024] = {0};
     int l_output = 0;
    /* ------------------ keluarin xml ------------------*/
        xmlrpc_value *params;
        xmlrpc_mem_block *xmlmemblockP = NULL;

    params = xmlrpc_build_value(&env, "(ii)", (xmlrpc_int32) 5, (xmlrpc_int32) 7);    
    xmlmemblockP = XMLRPC_MEMBLOCK_NEW(char, &env, 0);
    xmlrpc_serialize_call(&env, xmlmemblockP, "sample.sumAndDifference", params);


    l_output = snprintf(output,XMLRPC_MEMBLOCK_SIZE(char, xmlmemblockP),"%s",XMLRPC_MEMBLOCK_CONTENTS(char, xmlmemblockP));
    output[l_output] = '\0';

    printf("submit data -> \n %s\n",output);

    XMLRPC_MEMBLOCK_FREE(char, xmlmemblockP);

    /* Dispose of our parameter array. */
    xmlrpc_DECREF(params);

     /* ------------------ keluarin xml ------------------*/


    if(env.fault_occurred)
    {
    printf("err : %s\n",env.fault_string);
        return 0;
    }



    xmlrpc_int32 sum, difference;

    xmlrpc_decompose_value(&env, result, "{s:i,s:i,*}",
                       "sum", &sum,
                       "difference", &difference);

    /* keluarin xml respon */

    xmlmemblockP = XMLRPC_MEMBLOCK_NEW(char, &env, 0);

    xmlrpc_serialize_response(&env,xmlmemblockP,result);    
    l_output = snprintf(output,XMLRPC_MEMBLOCK_SIZE(char, xmlmemblockP),"%s",XMLRPC_MEMBLOCK_CONTENTS(char, xmlmemblockP));
    output[l_output] = '\0';    
    printf("respon data-> \n %s \n",output);
    XMLRPC_MEMBLOCK_FREE(char, xmlmemblockP);

    /* keluarin xml respon*/


    if(env.fault_occurred)
    {
        printf("err : %s\n",env.fault_string);
        return 0;
    }



    printf("Sum: %d, Difference: %d\n", (int) sum, (int) difference);



    xmlrpc_DECREF(result);


    xmlrpc_env_clean(&env);
    xmlrpc_client_cleanup();



return 0;
}
