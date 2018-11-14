#include <stdio.h>

#include <limits.h>
#include <ctype.h>

long long A[100001],B[100001];
long long C[100001];
long long N,m,M;

#define MAX LLONG_MAX
long long _max=0;
long long _ans=0;

typedef long long ll;
void swap(ll *a,ll *b)
{
  ll t=*a;  *a=*b; *b=t;
}
void maxHeapif(long long i)
{
  ll l=2*i;
  ll r=2*i + 1;
  ll g;
  if(l<N+1 && B[l]>B[i])
    g=l;
  else
   g=i;
  if(r<N+1 && B[r]>B[g])
   g=r;
  if(g!=i)
  {
    swap(&B[i],&B[g]);
    swap(&A[i],&A[g]);
    swap(&C[i],&C[g]);
    maxHeapif(g);
  } 
}
void buildHeap()
{
  ll i;
  for(i=N/2;i>0;--i)
  {
    maxHeapif(i);
  }
}
void parseint(ll *n)
{
    long long c;
    do { c = getchar_unlocked();} while(c<'0');
    *n = c - '0';
    /*while (isdigit((c = getchar_unlocked())))*/
    while ((c = getchar_unlocked()) >= '0')
        *n = 10*(*n) + c-'0';

}

void printarr(long long a[])
{
  int i;
  for(i=1;i<=N;++i)
    printf("%d ",a[i]);
  printf("\n");
}
ll tot=0;
void decrease()
{
  ll nextMax=B[2]; if(B[3]>nextMax)nextMax=B[3];
  long long c=1;
  while( (B[1]-C[1]*c) > nextMax && (m-c)>0){++c;}
  B[1]=B[1]-C[1]*c;
  A[1]=A[1]-c;
  tot-=c;
  m=m-c+1;
  maxHeapif(1);
}
int main()
{
  long long i;
#ifdef DEBUG
  long long L;
  scanf("%lld",&L);
  while(L--) {
  _max=0;
  _ans=0;
#endif
  scanf("%lld %lld",&N,&M);
  for(i=1;i<=N;++i)
  {
    parseint(&A[i]);tot+=A[i];
  }
  for(i=1;i<=N;++i)
  {
    parseint(&C[i]);
    B[i]=A[i]*C[i];
  }
printf("read ip\n");
#ifdef DEBUG
  printarr(B);
  printarr(A);
#endif
  buildHeap();
printf("built  heap\n");
#ifdef DEBUG
  printarr(B);
  printarr(A);
#endif
  long long n=N+1;
  m=M>tot?tot:M;
  while(m--)
  {
  //  A[getPos()]--;
    decrease();
    if(tot==0)break;
#ifdef DEBUG
  printarr(B);
  printarr(A);
#endif
  }
  printf("%lld\n",B[1]);
#ifdef DEBUG
  }
#endif
  return 0;
}

