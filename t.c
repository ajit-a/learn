#include <stdio.h>

int main()
{
	char *a="ajit";
	char b[]="amit";
	b[1]='j';
	printf("%s\n",b);
	a=b;
	return 0;
}
