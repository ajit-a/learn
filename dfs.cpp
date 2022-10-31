#include <vector>
#include <iostream>
#include <stack>

using namespace std;

class DFS {
    vector<int> &nodes;
    vector<pair<int,int>> &edges;
    vector<vector<int>> adj;
    vector<bool> visited;
    
    public:
    explicit DFS(int N,vector<int>& n,vector<pair<int,int>>& e):nodes(n),edges(e) {
        visited.resize(N,false);
        adj.resize(N);
        for(auto& p : edges) {
            adj[p.first].emplace_back(p.second);
        }
    }
    
    void run(int node) {
        if (visited[node])
            return;
        cout<<node<<endl;
        for(auto& n : adj[node]) {
            run(n);
        }
        visited[node] = true;
    }
    bool detectcycle(int n, vector<int>& vis) {
        if (vis[n] == 1) /*visited*/
            return true;
        if (vis[n] == 2) /*processed*/
            return false;
            
        vis[n] = 1;
        
        for(auto v : adj[n]) {
            if (detectcycle(v,vis)) {
                return true;
            }
        }
        vis[n] = 2;
        return false;
    }
    bool iscycle() {
        vector<int> visited(nodes.size(),0);
        for(int n : nodes) {
            if (!visited[n])
                if(detectcycle(n,visited))
                    return true;
        }
        return false;
    }
};

int main()
{
    {
    vector<int> nodes = {0,1,2,3,4};
    vector<pair<int,int>> edges = {{0,1},{0,2},{0,3},{2,4}};
    
    DFS dfs(nodes.size(),nodes,edges);
    cout<<"Cycle:"<<dfs.iscycle()<<endl;
    dfs.run(0);
    }
    {
    vector<int> nodes = {0,1,2,3,4,5};
    vector<pair<int,int>> edges = {{0,1},{1,5},{0,2},{0,3},{2,4},{2,5},{5,3},{3,2}};
    
    DFS dfs(nodes.size(),nodes,edges);
    if (dfs.iscycle()) {
        cout<<"Cycle Found"<<endl;
        return 0;
    }
    
    dfs.run(0);
    }
    return 0;
}
