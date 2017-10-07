#include <stdio.h>
typedef enum {Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday}Day;

int main()
{
	int i;
	Day d=2;
	char a[10];
	printf("Enter the day\n");
	scanf("%d",&i);
	printf("You selected :%d\n",(Day)d);
	return 0;
}
