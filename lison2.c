/*Longest increasing subsequence O(n ^ 2)*/
#include <stdio.h>
#include <string.h>
#define MAX 100
int array[MAX],DP[MAX],prev[MAX];
int maxLength = 1;
int N;
void find()
{
int  bestEnd = 0;
DP[0] = 1;
prev[0] = -1;
int i;
for (i = 1; i < N; i++)
{
   DP[i] = 1;
   prev[i] = -1;
   int j;

   for (j = i - 1; j >= 0; j--)
      if (DP[j] + 1 > DP[i] && array[j] < array[i])
      {
         DP[i] = DP[j] + 1;
         prev[i] = j;
      }

   if (DP[i] > maxLength)
   {
      bestEnd = i;
      maxLength = DP[i];
   }
}
}

int main()
{
	int i=0;
	memset(array,0,sizeof(int)*MAX);
	memset(DP,0,sizeof(int)*MAX);
	memset(prev,0,sizeof(int)*MAX);
	printf("Enter the number of digits :");
	scanf("%d\n",&N);
	while(i<N)
		scanf("%d",&array[i++]);
	find();
	printf("maxLength : %d\n",maxLength);
}
