#include <stdio.h>
#include <stdlib.h>

typedef struct test
{
	int roll;
	char *name;
}C;
typedef struct details
{
	int id;
	C *c;
}D;


D fun2()
{
	D d1;
	C *c = NULL;
	c = malloc(sizeof(C));
	c->name = "ajit";
	d1.id=1;
	c->roll = 2;
	d1.c=c;
	return (d1);	
}
fun1()
{
	D d;
	d = fun2();
	printf("%d\n",d.id);
	printf("%s\n",d.c->name);
	printf("%d\n",d.c->roll);
	free(d.c);
}

int main()
{
	fun1();
	return 0;
}
