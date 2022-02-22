#include <iostream>
#include<queue>
#include<algorithm>
using namespace std;

string Map[100001];
int T,N,M;

vector<pair<int,int> > mask={{-1,0},{0,1},{0,-1},{1,0}};

bool valid(int i,int j)
{
    return i>=0 && j>=0 && i<M && j<N;
}
int solve(int i,int j)
{
    std::queue<pair<int,int> > Q;
    Q.push({i,j});
    Map[i][j]='0';
    int sz=1;
    while(!Q.empty())
    {
        pair<int,int> P=Q.front();
        Q.pop();
        for(int k=0;k<4;++k)
        {
            int ii=P.first+mask[k].first;
            int jj=P.second+mask[k].second;
            if(valid(ii,jj) && Map[ii][jj]=='1')
            {
                Q.push({ii,jj});
                Map[ii][jj]='0';
                ++sz;
            }
        }
    }
    
    return sz;
}
int main() {
	
	cin>>T;
	while(T--)
	{
	    cin>>M>>N;
	    for(int i=0;i<N;i++)
	    {
	        cin>>Map[i];
	    }
	    vector<int> land_size;
	    for(int i=0;i<M;++i)
	    {
	        for(int j=0;j<N;++j)
	        {
	            if(Map[i][j]=='1')
	                land_size.push_back(solve(i,j));
	        }
	    }
	    sort(land_size.begin(),land_size.end(),greater<int>());
	    int ans=0;
	    for(int i=1;i<land_size.size();i=i+2)
	        ans+=land_size[i];
	    cout<<ans<<endl;
	}
	return 0;
}

