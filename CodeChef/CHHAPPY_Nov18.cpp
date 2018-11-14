#include <iostream>
#include <set>
#include <vector>
#include <cstring>


using namespace std;

#define MAX 100002
typedef set<int> seti;
int main()
{
  bool lookup[MAX];
  int arr[MAX];
  int T,N,n;
  cin>>T;
  while(T--)
  {
    memset(lookup,0,sizeof(lookup));
    cin>>N;
    vector< set<int> > v(MAX);
    for(int i=1;i<=N;++i)
    {
      cin>>n;
      if(lookup[n])
      {
        v[n].insert(i);
      }
      else
      {
        seti s;s.insert(i);
        v[n]=s;
        lookup[n]=true;
      }
    }
    int found;
    for(int i=1;i<=N;++i)
    {
        found=0;
	seti s = v[i];
        if(!s.empty())
        {
          seti::iterator it;
          for(it=v[i].begin();it!=v[i].end();++it)
          {
            if(lookup[*it])
             ++found;
            if(found>1)break;
          }
        }
        if(found>1)break;
    }
    if(found>1)cout<<"Truly Happy"<<endl;
    else cout<<"Poor Chef"<<endl;
  }
}
