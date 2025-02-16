#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> 
#include <cmath>
#include <set>
#define ll long long
#define pb push_back
using namespace std;

const ll maxN = 1e6 + 7;
ll n, m;
vector<ll> adj[maxN], par(maxN), sz(maxN);

void make_set(ll a){
  par[a] = a;
  sz[a] = 1;
}


ll find_set(ll v){
  if (v == par[v]){
    return v;
  }
  ll p = find_set(par[v]);
  par[v] = p;
  return p;
}

void union_set(ll a, ll b){
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
}

void solve() {
    
}


void input() {  
    cin >> n >> m ;
    for (int i = 1;i <= n;++i) make_set(i);
    for (int i = 0;i < m;++i){
      ll u, v;
      cin >> u >> v;
      if (find_set(u) != find_set(v)){
        union_set(u, v);
        n--;
      }
      cout << n << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    input();
    return 0;
}
