#include <stdio.h>

int C[10];
int opt[50][50];
int maxC;
int amount;
void init()
{
	int i,j;
	for(i=0;i<maxC;i++)
		opt[i][0]=0;
	for(i=1;i<=amount;i++)
		opt[0][i]=(i%C[0]==0)?i/C[0]:0;
		//opt[0][i]=(i/C[0])+(i%C[0]);
	for(i=1;i<maxC;i++)
	{
		for(j=1;j<=amount;j++)
		{
			if(j<C[i])
			{
				opt[i][j]=opt[i-1][j];
			}
			else
			{
				opt[i][j] = (opt[i-1][j]<(1+opt[i][j-C[i]]))?opt[i-1][j]:(1 + opt[i][j-C[i]]);
			}
		}
	}
}
void display()
{
	int i,j;
	for(i=0;i<maxC;i++)
	{
		for(j=1;j<=amount;j++)
		{
			printf("%d ",opt[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	int i;
	printf("Enter the number of denominations\n");
	scanf("%d",&maxC);
	printf("Enter the value of denominations\n");
	for(i=0;i<maxC;i++)
	{
		scanf("%d",&C[i]);
	}
	printf("Enter the amount\n");
	scanf("%d",&amount);
	init();
	display();
	return 0;
}
