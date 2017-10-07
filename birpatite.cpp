/*To check for birpatite graph using adjacency list and DFS*/
#include<iostream>
#define v 9
#include<vector>
#include <stdio.h>
using namespace std;
class graph
{
	vector<int>*adj;
	public:
		graph();
		void addedge(int x,int y);
		bool dfs(bool visited[],int color[],int current,int rang);
};
graph::graph()
{
	adj=new vector<int>[v];
}
void graph::addedge(int x,int y)
{
	adj[x].push_back(y);
	adj[y].push_back(x);
}
bool graph::dfs(bool visited[],int color[],int current,int rang)
{
	visited[current]=true;
	vector<int>::iterator p;
	for(p=adj[current].begin();p!=adj[current].end();p++)
	{
		if(visited[*p])
		{
			if(color[*p]==color[current])
			return false;
		}
		else
		{
			if(rang==0)
			{
				color[*p]=1;
				if(dfs(visited,color,*p,1))
				return true;
			}
			else
			{
				color[*p]=0;
				if(dfs(visited,color,*p,0))
				return true;
		    }
		    return false;
		}
	}
	return true;
}
int main(void)
{
	graph g;
	g.addedge(0,5);
	g.addedge(1,5);
	g.addedge(1,6);
	g.addedge(2,7);
	g.addedge(2,8);
	g.addedge(3,6);
	g.addedge(4,5);
	g.addedge(4,8);
	int i,j,flag=0;
	int color[v];
	bool visited[v];
	for(i=0;i<=v-1;i++)
	visited[i]=false;
	for(i=0;i<=v-1;i++)
	color[i]=false;
	for(i=0;i<=v-1;i++)
	{
				printf("i:%d\n",i);
				int k;
				printf("visited :");for(k=0;k<v;k++)printf("%d  ",visited[k]);printf("\n");
				printf("color   :");for(k=0;k<v;k++)printf("%d  ",color[k]);printf("\n\n");
		if(!visited[i])
		{
		    	color[i]=0;
				int k;
				printf("visited :");for(k=0;k<v;k++)printf("%d  ",visited[k]);printf("\n");
				printf("color   :");for(k=0;k<v;k++)printf("%d  ",color[k]);printf("\n\n");
			if(g.dfs(visited,color,i,0))
			{
			continue;
			}
			else
			{
				flag=1;
				break;
			}	
		}
	}
	if(flag==0)
	{
		cout<<"the graph is bipartite"<<'\n';
		for(i=0;i<=v-1;i++)
		cout<<color[i]<<' ';
		cout<<'\n';
	}
	else
	cout<<"the graph contains an odd edged cycle"<<'\n';
	return 0;
}


