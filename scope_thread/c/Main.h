#include <pthread.h>

struct params
{
	int a;
	int b;
};
#ifdef __cplusplus
extern "C"	
	{
	void *sum(void*);
	}
#endif
