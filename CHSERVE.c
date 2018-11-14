#include <stdio.h>

int main()
{
int N;
long long P,Q,K;

scanf("%d",&N);
while(N--)
{
  scanf("%lld %lld %lld",&P,&Q,&K);
  if(  (( (P+Q)/K )&1) == 0  )
  {
    printf("CHEF\n");
  }
  else
  {
   printf("COOK\n");
  }
}
  return 0;
}
