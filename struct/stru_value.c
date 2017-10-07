#include <stdio.h>

typedef struct product
{
	char name[10];
	int price;
	float weight;
}product;
int main()
{
	int i,n;
	product p[10];
	printf("Enter no of prducts\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%s %d %f",p[i].name,&p[i].price,&p[i].weight);
	}
	print_prods(p,n);
	return 0;
}
void print_prods(product p[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("Name:%s\tPrice:%d\tWeight:%f\n",p[i].name,p[i].price,p[i].weight);
	}
}

