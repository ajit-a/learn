#include <stdio.h>

int main()
{
  int T,i;
  int n;
  scanf("%d",&T);
  for(i=0;i<T;++i)
  {
    scanf("%d",&n);
    if(i==T-1)
    printf("%d %lld",1,1L<<n);
    else
    printf("%d %lld ",1,1L<<n);
  }
  printf("\n");
  return 0;
}
