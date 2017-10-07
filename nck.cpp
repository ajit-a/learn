#include<vector>
#include<stack>
#include<set>
#include<map>
#include<queue>
#include<deque>
#include<string>

#include<iostream>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<cstdlib>
#include<cstdio>
#include<cmath>

using namespace std;

#define FOR(i,a,b)					for(int i=a;i<b;i++)
#define REP(i,n)					FOR(i,0,n)
#define pb						 	push_back
#define mp						 	make_pair
#define s(n)						scanf("%d",&n)
#define sl(n) 						scanf("%lld",&n)
#define sf(n) 						scanf("%lf",&n)
#define ss(n) 						scanf("%s",n)
#define fill(a,v) 					memset(a, v, sizeof a)
#define sz							size()
#define INF							(int)1e9
#define EPS							1e-9
#define bitcount					__builtin_popcount
#define all(x)						x.begin(), x.end()
#define gcd							__gcd
#define maX(a,b)					(a>b?a:b)
#define miN(a,b)					(a<b?a:b)

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef long long LL;
typedef pair<int, int > PII;


const LL mod = 1000000007ll;

pair<LL,LL> extGCD(LL a,LL b)
{
	if(b==0) return mp(1ll,0ll);
	else
	{
		pair<LL,LL> temp = extGCD(b,a%b);
		return mp( temp.second, temp.first - (a/b) * temp.second);
	}
}


LL inverse(LL a)
{
	pair<LL,LL> temp = extGCD(a,mod);
	LL x = temp.first;
	while(x<0) x+=mod;
	while(x>=mod) x-=mod;
	return x;
}
 

LL nCk(LL n,LL k)
{
	if(k>n/2) k=n-k;
	LL num=1,den=1;
	
	for(LL i=1;i<=k;i++)
	{
		num = (num*n) % mod;
		den = (den*i) % mod;
		n--;
	}
	
	return (num * inverse(den)) % mod;
}

int main(int argc,char *argv[])
{
	printf("%lld\n",nCk(atoi(argv[1]),atoi(argv[2])));
	return 0;
}
