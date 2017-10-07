#include <stdio.h>
#include <math.h>

#define K 7

int t[7]={2,3,5,7,11,13,17};
int S[30];
void fillS()
{
	int i;
	S[0]=1;
	for(i=1;i<30;i++)
		S[i]=S[i-1]<<1;
}
void findD(int *p,int *d,int n)
{
	int i;
	for(i=29;i>0;i--)
	{
		if(S[i]>n)
			continue;
		if(n%S[i]==0 && (n/S[i])%2!=0)
		{
			*p=i;
			*d=n/S[i];
			return;
		}
	}
}
int power(int a,int b,int mod)
{
	long long i;
	i=(a*a)%mod;
	while(b-- > 2)
	{
		printf("i:%ld b:%ld\n",i,b);
		i = (i*a)%mod; /* a because I am raising 2 else it shoule be i */
	}
	//printf("i:%ld\n",i);
	return i;
}
int checkPrime(int N)
{
	int i,d=0,s=0,j=0;
	if(N%2==0)
		return -1;
	else
		findD(&s,&d,(N-1));
	if(d==0){printf("cannot compute\n");exit(0);}
	printf("s:%ld d:%ld\n",s,d);
	for(i=0;i<K;i++)
	{
		j=0;
		int x=power(t[i]<<j,d,N);
		if(x == (N-1) || x ==1){return 0;}
		for(j=1;j<=s-1;j++)
		{
			x=power(x,2,N);
			if(x == (N-1))
			{
				return 0;
			}
			if(x == 1)
			{
				continue;
			}
		}
	}
	return -1;
}
int main()
{
	fillS();
	long long N;
	while(1)
	{
	scanf("%lld",&N);
	int p=checkPrime(N);
	if(p==0)
		printf("Prime\n");
	if(p==-1)	
		printf("Not Prime\n");
	}
	return 0;
}
