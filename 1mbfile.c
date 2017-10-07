#include<stdio.h>

int main(int argc,char* argv[])
{
	FILE *fp;
	int i=0;
	fp=fopen((char*)argv[1],"a+");
	while(i<(1024*1024))
	{
		fprintf(fp,"A");
		i++;
	}
	fclose(fp);
	return 0;
}
