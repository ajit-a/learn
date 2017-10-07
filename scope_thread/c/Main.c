#include "Main.h"
#include <stdio.h>

void *sum(void* in)
{
	struct params *pm = (struct params *)in;
	printf("Sum :%d\n",pm->a + pm->b);
}
