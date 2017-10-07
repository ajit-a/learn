#include <stdio.h>
#include <signal.h>
void int_handler(int sing)
{
	printf("Interrupt recieved\n");
}
int main()
{
	signal(SIGINT,int_handler);
	while(1){}
	return 0;
}
