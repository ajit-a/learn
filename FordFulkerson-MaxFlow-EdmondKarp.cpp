/*Original code taken from https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
Sample problem taken from https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/shubham-and-grid-806c2c66/
*/

/*
The time complexity of Edmond Karp Implementation is O(VE2). In this post, a new Dinic’s algorithm is discussed which is a faster algorithm and takes O(EV2).

Like Edmond Karp’s algorithm, Dinic’s algorithm uses following concepts : 

A flow is maximum if there is no s to t path in residual graph.
BFS is used in a loop. There is a difference though in the way we use BFS in both algorithms.
In Edmond’s Karp algorithm, we use BFS to find an augmenting path and send flow across this path. 
In Dinic’s algorithm, we use BFS to check if more flow is possible and to construct level graph. 
In level graph, we assign levels to all nodes, level of a node is shortest distance (in terms of number of edges) of the node from source. 
Once level graph is constructed, we send multiple flows using this level graph. 
This is the reason it works better than Edmond Karp. In Edmond Karp, we send only flow that is send across the path found by BFS.
https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/
*/
// C++ program for implementation of Ford Fulkerson
// algorithm
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

// Number of vertices in given graph
#define V 18

/* Returns true if there is a path from source 's' to sink
't' in residual graph. Also fills parent[] to store the
path */
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
	// Create a visited array and mark all vertices as not
	// visited
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	// Create a queue, enqueue source vertex and mark source
	// vertex as visited
	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS Loop
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {
				// If we find a connection to the sink node,
				// then there is no point in BFS anymore We
				// just have to set its parent and can return
				// true
				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// We didn't reach sink in BFS starting from source, so
	// return false
	return false;
}

// Returns the maximum flow from s to t in the given graph
//template<typename T>
int fordFulkerson(vector<vector<pair<int,int>>>& graph, int s, int t)
{
	int u, v;

	// Create a residual graph and fill the residual graph
	// with given capacities in the original graph as
	// residual capacities in residual graph
	int rGraph[V][V] = {0}; // Residual graph where rGraph[i][j]
				// indicates residual capacity of edge
				// from i to j (if there is an edge. If
				// rGraph[i][j] is 0, then there is not)

    for (u=0; u< V; ++u) {
        for (auto& p : graph[u]) {
            rGraph[u][p.first] = p.second;
        }
    }
	
	int parent[V]; // This array is filled by BFS and to
				// store path

	int max_flow = 0; // There is no flow initially

	// Augment the flow while there is path from source to
	// sink
	while (bfs(rGraph, s, t, parent)) {
		// Find minimum residual capacity of the edges along
		// the path filled by BFS. Or we can say find the
		// maximum flow through the path found.
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		// update residual capacities of the edges and
		// reverse edges along the path
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}

	// Return the overall flow
	return max_flow;
}

// Driver program to test above functions
int main()
{
	// Let us create a graph shown in the above example
	int graph[V][V]
		= { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
			{ 0, 4, 0, 0, 14, 0 }, { 0, 0, 9, 0, 0, 20 },
			{ 0, 0, 0, 7, 0, 4 }, { 0, 0, 0, 0, 0, 0 } };
    vector<vector<pair<int,int>>> newgraph; newgraph.reserve(V);
    newgraph[0].push_back({2,1});
    newgraph[0].push_back({3,1});
    newgraph[2].push_back({1,1});
    newgraph[1].push_back({9,1});
    newgraph[9].push_back({5,1});
    newgraph[5].push_back({13,1});
    newgraph[13].push_back({6,1});
    newgraph[6].push_back({17,1});
    newgraph[3].push_back({4,1});
    newgraph[4].push_back({12,1});
    newgraph[12].push_back({8,1});
    newgraph[8].push_back({16,1});
    newgraph[16].push_back({7,1});
    newgraph[7].push_back({17,1});
    

    /* Below edges are probably not required
    newgraph[2].push_back({0,0});
    newgraph[3].push_back({0,0});
    newgraph[1].push_back({2,0});
    newgraph[9].push_back({1,0});
    newgraph[5].push_back({9,0});
    newgraph[13].push_back({5,0});
    newgraph[6].push_back({13,0});
    newgraph[17].push_back({6,0});
    newgraph[4].push_back({3,0});
    newgraph[12].push_back({4,0});
    newgraph[8].push_back({12,0});
    newgraph[16].push_back({8,0});
    newgraph[7].push_back({16,0});
    newgraph[17].push_back({7,0});*/
    
    auto ans = fordFulkerson(newgraph, 0, V-1)
	cout << "The maximum possible flow is "
		<< ans<<endl;

	return 0;
}
/*
Below are the setter and tester code of actual problem for reference
//let's do it
 #include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define inf 1000000000000
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define all(v) v.begin(),v.end()
#define S second
#define F first
#define boost1 ios::sync_with_stdio(false);
#define boost2 cin.tie(0);
#define mem(a,val) memset(a,val,sizeof a)
#define endl "\n"
#define maxn 100001

struct Edge 
{
  ll from, to, cap, flow, index;
  Edge(ll from, ll to, ll cap, ll flow, ll index) :
  from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel
{
  ll N;
  vector<vector<Edge> > G;
  vector<ll> excess;
  vector<ll> dist, active, count;
  queue<int> Q;

  PushRelabel(ll N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(ll from, ll to, ll cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

  void Enqueue(ll v) {
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
  }

  void Push(Edge &e) {
    ll amt=min(excess[e.from], e.cap - e.flow);
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }

  void Gap(ll k) {
    for (ll v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(ll v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (ll i = 0; i < G[v].size(); i++)
      if (G[v][i].cap - G[v][i].flow > 0)
	dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(ll v) {
    for (ll i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)
	Gap(dist[v]);
      else
	Relabel(v);
    }
  }

  ll GetMaxFlow(ll s, ll t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (ll i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }

    ll totflow = 0;
    for (ll i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
  vector<vector<Edge> > build(){
	return G;
  }
};
int id[25][25],n,m;
char arr[25][25];
int di[]={1,-1,0,0};
int dj[]={0,0,1,-1};

int valid(int x,int y)
{
	return (x>=1 && x<=n && y>=1 && y<=m);
}
int main()
{
	boost1;boost2;
	int i,j,x,y,ctr=0,src,sink,ni,nj,k;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		cin>>arr[i][j];
	}
	ctr=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			ctr++;
			id[i][j]=ctr;
		}
	}
	PushRelabel network(2+2*n*m);
	src=0;
	sink=1+2*n*m;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(arr[i][j]=='a')
			{
				network.AddEdge(src,id[i][j],1);
				for(k=0;k<4;k++)
				{
					ni=i+di[k];
					nj=j+dj[k];
					if(!valid(ni,nj) || arr[ni][nj]!='b')
					continue;
					network.AddEdge(id[i][j],id[ni][nj],1);
				}
			}
			else if(arr[i][j]=='b')
			{
				network.AddEdge(id[i][j],n*m+id[i][j],1);
				for(k=0;k<4;k++)
				{
					ni=i+di[k];
					nj=j+dj[k];
					if(!valid(ni,nj) || arr[ni][nj]!='c')
					continue;
					network.AddEdge(n*m+id[i][j],id[ni][nj],1);
				}
			}
			else if(arr[i][j]=='c')
			{
				network.AddEdge(id[i][j],n*m+id[i][j],1);
				for(k=0;k<4;k++)
				{
					ni=i+di[k];
					nj=j+dj[k];
					if(!valid(ni,nj) || arr[ni][nj]!='d')
					continue;
					network.AddEdge(n*m+id[i][j],id[ni][nj],1);
				}
			}
			else
			network.AddEdge(id[i][j],sink,1);
		}
	}
	cout<<network.GetMaxFlow(src,sink);
	return 0;
}
Tester
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 20;

const int MAXNODE = MAXN * MAXN * 2 + 2;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m, source, sink;
char a[MAXN][MAXN];
int mark[256], x[4], y[4];

vector<int> vtx, capacity, nextEdge;
int head[MAXNODE];

void addEdge(int a, int b)
{
    vtx.push_back(b);
    nextEdge.push_back(head[a]);
    head[a] = capacity.size();
    capacity.push_back(1);

    vtx.push_back(a);
    nextEdge.push_back(head[b]);
    head[b] = capacity.size();
    capacity.push_back(0);
}

void generate(int i)
{
    if (i == 4) {
        addEdge(source, mark['a']);
        addEdge(mark['a'] + n * m, mark['b']);
        addEdge(mark['b'] + n * m, mark['c']);
        addEdge(mark['c'] + n * m, mark['d']);
        addEdge(mark['d'] + n * m, sink);
        return;
    }
    for (int j = i - 1; j < i; ++ j) {
        for (int k = 0; k < 4; ++ k) {
            int tx = x[j] + dx[k], ty = y[j] + dy[k];
            if (tx >= 0 && ty >= 0 && tx < n && ty < m && 
                a[tx][ty] == 'a' + i) {
                mark[a[tx][ty]] = tx * m + ty;
                x[i] = tx;
                y[i] = ty;
                generate(i + 1);
                mark[a[tx][ty]] = -1;
            }
        }
    }
}

bool bfs()
{
    queue<int> q;
    vector<int> pre(sink + 1, -1);
    q.push(source);
    pre[source] = -2;
    while (q.size() && pre[sink] == -1) {
        int u = q.front();
        q.pop();
        for (int p = head[u]; p != -1; p = nextEdge[p]) {
            if (capacity[p]) {
                int v = vtx[p];
                if (pre[v] == -1) {
                    pre[v] = p;
                    q.push(v);
                }
            }
        }
    }
    if (pre[sink] == -1) {
        return false;
    }
    for (int u = sink, p; u != source; u = vtx[p]) {
        p = pre[u];
        -- capacity[p];
        ++ capacity[p ^= 1];
    }
    return true;
}

int main()
{
    assert(scanf("%d%d", &n, &m) == 2 && 1 <= n && n <= MAXN && 1 <= m && m <= MAXN);
    source = 2 * n * m;
    sink = source + 1;
    memset(head, -1, sizeof(head));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            char s[10];
            assert(scanf("%s", s) == 1);
            assert(strlen(s) == 1);
            a[i][j] = s[0];
            assert('a' <= a[i][j] && a[i][j] <= 'd');
            if (a[i][j] <= 'd') {
                addEdge(i * m + j, i * m + j + n * m);
            }
        }
    }
    cerr << "I/O: " << capacity.size() << endl;

    memset(mark, -1, sizeof(mark));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (a[i][j] == 'a') {
                x[0] = i;
                y[0] = j;
                mark['a'] = i * m + j;
                generate(1);
            }
        }
    }
    cerr << "Generation done: " << capacity.size() << endl;

    int flow = 0;
    while (bfs()) {
        ++ flow;
    }
    printf("%d\n", flow);

    return 0;
}
*/
