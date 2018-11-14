#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include<iostream>

using namespace std;

#define MAX 100002

long arr[MAX];

typedef struct pos
{
  long l,r;
}stpos;

long positions[MAX];
long lpos=0;

stpos* lookup;
//stpos* lookup[2*MAX];
long lookup_index=0;
long N,Q,K,i;
long _max=0;
void ADD(long l,long r)
{
//  stpos *s=(stpos*)malloc(sizeof(stpos));
  lookup[lookup_index].l=l;
  lookup[lookup_index].r=r;
  lookup_index++;
}

long getposl(long i)
{
  while(arr[i]!=1 && i<N)++i;
  return i;
}
long getposr(long i)
{
  while(arr[i]!=0 && i<N)++i;
  return i-1;
}
long ans[MAX];
long lans=0;
void genPos()
{
  long l,r,diff=0;
  for(i=0;i<N;i=r+1)
  {
    if(arr[i]==1)
    {
      l=i;
      if(l==N-1)
      {
       r=l;
       ADD(l,r);return;
      }
    }
    else
    {
     l=getposl(i);
     if(l==N)
      return;
    } 
    r=getposr(l+1);
    diff=r-l+1;
    
      if(diff>_max)_max=diff;
      ADD(l,r);
   }
   if(_max>K)
   {
     _max=K;
   }
   ans[lans++]=_max;
}
void plup(vector<bool> &v,long j)
{
  return;
  if(j==1)cout<<"IN"<<endl;
  if(j==2)cout<<"OUT"<<endl;
  for(long i=0;i<N;++i)cout<<v[i]<<" ";
  cout<<endl;
  for(long i=0;i<lookup_index;++i)
  {
    cout<<lookup[i].l<<","<<lookup[i].r<<endl;
  }
}
void MoveAndCompute1(vector<bool> &v,long delta)
{
  for(int i=N-1;i>0;--i)
  {
    v[i]=v[i-1];
  }
}
void MoveAndCompute(vector<bool> &v,long delta)
{
  plup(v,1);
  for(int j=0;j<delta;++j)
  {
  bool b=v.back();
  v.erase(v.end());
  v.insert(v.begin(),b);
  }
  _max=1;
   long diff=0;
  for(long j=0;j<lookup_index;++j)
  {
/*
if(j==2)
{
  cout<<"v[lookup[j].l]:"<<v[lookup[j].l]<<endl;
  cout<<"v[lookup[j].r]:"<<v[lookup[j].r]<<endl;
}*/
    if(v[lookup[j].l]==1)
    {
      long t = lookup[j].r + delta;
      if(t >= N)
      {
        lookup[j].r = N-1;
      }
      else
      {
        lookup[j].r += delta;
      }
      diff=lookup[j].r - lookup[j].l + 1;
      if(diff>_max)
      {
        _max=diff;
      }
    }
    else
    {
      if(lookup[j].l == N-1)
      {
        lookup[j].l=0;
        lookup[j].r=0;
      }
      else {
      long t = lookup[j].l + delta;
      if(t >= N)
       lookup[j].l=N-1;
      else
       lookup[j].l += delta;
      t = lookup[j].r + delta;
      if(t >= N-1)
       lookup[j].r=N-1;
      else
       lookup[j].r += delta;
      diff=lookup[j].r - lookup[j].l + 1;
      if(diff>_max)
      {
        _max=diff;
      }
     }
    }
  }
  if(v[1]==0 && v[0]==1)
  {
    lookup[lookup_index].r=0;
    lookup[lookup_index].l=0;
    lookup_index++;
  }
  if(diff>K)_max=K;
  plup(v,2);
  if(_max>K)_max=K;
  ans[lans++]=_max;
}
int main()
{
  scanf("%ld%ld%ld",&N,&Q,&K);
  lookup=(stpos*)malloc(sizeof(stpos)*2*MAX);
  bool allZero=true;
  for(i=0;i<N;++i)
  {
    scanf("%ld",&arr[i]);
    if(allZero && arr[i])allZero=false;
  }
  vector<bool> v(arr,arr+N);
  char c[3*MAX];
  scanf("%s",c);
  int query[3*MAX];
  long j=0,L=0,_cntM=0;
  for(i=0;i<N;++i)
  {
    MoveAndCompute1(v,1);
  }
  long moves=0;
  for(i=0;i<Q;++i)
  {
    if(c[i]=='?')
    {
      printf("%ld\n",ans[moves]); 
    }
    else
    {
      ++moves;
      if(moves==lans)
        moves=0;
    }
  }
  return 0;
}
