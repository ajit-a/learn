#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include<iostream>

using namespace std;

#define MAX 100002

long arr[MAX];
long prefix[MAX];

typedef struct pos
{
  long l,r;
}stpos;

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
      if(diff>K)
      {
        _max=K;
      }
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
      long diff=lookup[j].r - lookup[j].l + 1;
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
      long diff=lookup[j].r - lookup[j].l + 1;
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
  if(_max>K)_max=K;
  plup(v,2);
}
long prefixLength=0;
void fillPrefix()
{
  long cnt=0;
  long j=0; 
  for(long i=0;i<N;++i)
  {
    if(arr[i]==0) 
    {
      while(arr[i]!=1 && i<N){++i;++cnt;}
      prefix[j++]=-cnt;
      --i;
      cnt=0;
    }
    else
    {
      while(arr[i]!=0 && i<N){++i;++cnt;}
      prefix[j++]=cnt;
      --i;
      if(cnt>_max)_max=cnt;
      cnt=0;
    }
  }
  prefixLength=j;
  if(_max>K)_max=K;
}
void updatePrefix(long delta=1)
{
  long lmax=_max;
  _max=1;
#if 0
  long e=prefix[prefixLength-1];
  long s=prefix[0];
  if(s<0 && e<0)
  {
    --prefixLength;
    _max=lmax;
  }
  else if(s<0)
  {
    prefix[prefixLength-1]-=1;
    if(prefix[prefixLength-1]!=0)
      ++prefixLength;
    for(long i=prefixLength-1;i>0;--i)
    {
      prefix[i]=prefix[i-1];
      if(prefix[i]>_max)_max=prefix[i];
    }
    prefix[0]=1;
    if(prefix[0]>_max)_max=prefix[0];
  }
  else if(e<0)
  {
    //++prefixLength;
    for(long i=prefixLength-1;i>0;--i)
    {
      prefix[i]=prefix[i-1];
      if(prefix[i]>_max)_max=prefix[i];
    }
    prefix[0]=e;
    if(prefix[0]>_max)_max=prefix[0];
  }
  else
  {
    prefix[0]+=1;
    prefix[prefixLength-1]-=1;
    if(prefix[prefixLength-1]==0)
    {
      --prefixLength;
      /*for(long i=prefixLength-1;i>0;--i)
      {
        if(prefix[i]>_max)_max=prefix[i];
      }*/
      _max=lmax;
      if(prefix[0]>_max)_max=prefix[0];
    }
    else
    {
      if(prefix[0]>_max)_max=prefix[0];
      if(prefix[prefixLength-1]>_max)_max=prefix[prefixLength-1];
    }
  }
#else
  long s=prefix[0];
  long e=prefix[prefixLength-1];
  if(s>0 && e>0) 
  {
    prefix[0] += 1;
    prefix[prefixLength-1] -= 1;
    if(e==1)
      --prefixLength;
    if(prefix[0]>_max)_max=prefix[0];
    if(prefix[prefixLength-1]>_max)_max=prefix[prefixLength-1];
  }
  else if (s<0 && e<0)
  {
    prefix[0] -= 1;
    prefix[prefixLength-1] += 1;
    if(e==-1)
      --prefixLength;
    _max = lmax;
  }
  else if(s>0 && e<0)
  {
      if(e==-1)
      {
        for(long i=prefixLength-1;i>0;--i)
        {
          prefix[i] = prefix[i-1];
          if(prefix[i]>_max)_max=prefix[i];
        }
        prefix[0] = e;
      }
      else
      {
        prefix[prefixLength-1] += 1;
        for(long i=prefixLength;i>0;--i)
        {
          prefix[i] = prefix[i-1];
          if(prefix[i]>_max)_max=prefix[i];
        }
        prefix[0] = -1;
        ++prefixLength;
      }
  }
  else if(s<0 && e>0)
  {
      if(e==1)
      {
        for(long i=prefixLength-1;i>0;--i)
        {
          prefix[i] = prefix[i-1];
          if(prefix[i]>_max)_max=prefix[i];
        }
        prefix[0] = e;
      }
      else
      {
        prefix[prefixLength-1] -= 1;
        for(long i=prefixLength;i>0;--i)
        {
          prefix[i] = prefix[i-1];
          if(prefix[i]>_max)_max=prefix[i];
        }
        if(prefix[prefixLength]>_max)_max=prefix[prefixLength];
        prefix[0] = 1;
        ++prefixLength;
      }
  }
  else
  {
    cout<<"unhandled"<<endl;
  }
#endif
  if(_max>K)_max=K;
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
  char c[3*MAX];
  scanf("%s",c);
/*
  vector<bool> v(arr,arr+N);
  if(!allZero)
  {
    genPos();
  }
  int query[3*MAX];
  long j=0,L=0,_cntM=0;
  for(i=0,j=0;i<Q;++i)
  {
    if(c[i]=='!')
    {
      while(c[i]!='?' && i<Q){++_cntM;++i;}
      --i;
      query[j++]=_cntM;
      _cntM=0;
    }
    else
    {
      query[j++]=-1;
    }
  }
  L=j;
  for(i=0;i<L;++i)
  {
    if(query[i]==-1)
    {
      printf("%ld\n",_max); 
    }
    else if(!allZero)
    {
      MoveAndCompute(v,query[i]);
    }
  }
*/
  if(!allZero)
    fillPrefix();
  for(i=0;i<Q;++i)
  {
    if(c[i]=='?')
    {
      printf("%ld\n",_max); 
    }
    else if(!allZero)
    {
  for(int j=0;j<prefixLength;++j)cout<<prefix[j]<<" ";cout<<endl;
      updatePrefix(1);
  for(int j=0;j<prefixLength;++j)cout<<prefix[j]<<" ";cout<<endl;
    }
  }
  return 0;
}
