#include <iostream> 
#include <vector> 
using namespace std;
#define ll long long

vector<vector<int>> adj(50005);
vector<int> ans(50005, 0);
vector<int> sz(50005, 1); // size of subtree rooted at each node
vector<int> dis(50005, 0); // sum of distance from the root (initially 0)
int n;

void dfs(int node, int par){
    for (auto child : adj[node]){
        if (child != par){
            dfs(child, node);
            sz[node] += sz[child];
            dis[node] += dis[child] + sz[child];
        }
    }
}



void dfs2(int node, int par){
    // reroot at current node
    ans[node] = dis[node];
    for (auto child : adj[node]){
        if (child != par){
          int old_dis = dis[node];
          int old_child_dis = dis[child];                           
          dis[node] -= dis[child] + sz[child];              // reroot from current node to child node
          dis[child] += dis[node] + (n - sz[child]);

          dfs2(child, node);

          dis[node] = old_dis;                               // reroot back 
          dis[child] = old_child_dis;
        }
    }
}
void solve(){
    // first dfs to compute the dist for each node as root 0
    dfs(0, -1);
    // second dfs to reroot and compute distances for each node as root
    dfs2(0, -1);
}

void input(){ 
    cin >> n;
    for (int i = 0;i < n - 1;++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    input();
    return 0;
}