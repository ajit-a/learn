#include <stdio.h>

int main(int argc,char *argv[])
{
	int i;
	char *ptr=NULL;
	printf("Value for %s is : %s\n",argv[1],getenv(argv[1]));

	if( strlen((ptr = getenv(argv[1]))) == 0)
		printf("Variable %s not defined\n",argv[1]);
	else
		printf("Value for %s is : %s\n",argv[1],ptr);
	return 0;
}
