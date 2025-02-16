#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
#define pb push_back
using namespace std;

const ll maxN = (long long) 1e6;

ll n, logn;
vector<ll> adj[maxN], depth(maxN, 0);
vector<vector<ll>> up(maxN, vector<ll>(20, -1));

void dfs(ll u, ll p){
    up[u][0] = p; 
    for (int j = 1; j <= logn; ++j) {
        if (up[u][j - 1] != -1) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        } else {
            up[u][j] = -1;
        }
    }

    for (auto &v : adj[u]) {
        if (v != p) {  
            depth[v] = depth[u] + 1;  
            dfs(v, u);
        }
    }
}

ll getKthAncestor(ll v, ll k) {
    for (int j = 0; j <= logn; ++j) {
        if (k & (1 << j)) {
            v = up[v][j];
            //if (v == -1) break; 
        }
    }
    return v;
}

int main() {
    cin >> n;
    logn = ceil(log2(n));
    
    for (int i = 0; i < n - 1; ++i) {
        ll x, y; 
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    
    dfs(1, -1);
    ll node, k;
    cin >> node >> k;
    cout <<  getKthAncestor(node, k);

    return 0;
}
