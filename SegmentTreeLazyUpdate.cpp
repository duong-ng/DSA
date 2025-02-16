#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <climits>
#include <map>
#include <stack>
#include <algorithm>
#define ll long long
#define pll pair<long long, long long>
using namespace std;
 
const ll maxN = int(1e6) + 6;
 
ll t, n, q;
vector<ll> a(maxN);
 
class SegmentTree{
private :
    vector <ll> t, lazy;
    void push(ll id, ll l, ll r){
        if (lazy[id]){
           t[id] += (r - l + 1) * lazy[id];
           if (l != r){
            lazy[id * 2] += lazy[id];
            lazy[id * 2 + 1] += lazy[id];
           }
           lazy[id] = 0;
        }
    }   
    void build(ll id, ll l, ll r, vector<ll> &a){
        if (l == r) {
            t[id] = a[l];
            return;
        }
        ll mid = l + r >> 1;
        build(id * 2, l, mid, a);
        build(id * 2 + 1,mid + 1, r, a);
        t[id] = t[id * 2] + t[id * 2 + 1];
    }
    ll get(ll id, ll l, ll r, ll u, ll v){
        push(id, l, r);
        if (r < u || v < l){
            return 0;
        }
        if (l >= u && r <= v){
            return t[id];
        }
        ll mid = l + r >> 1;
        return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r,u, v);
    }
    void update(ll id, ll l, ll r, ll u, ll v, ll val){
        push(id, l, r);
        if (u > r || v < l){
            return;
        }
        if (l >= u && v >= r){
            lazy[id] += val;
            push(id, l, r);
            return;
        }
        ll mid = l + r >> 1;
        update(id * 2, l, mid, u, v, val);
        update(id * 2 + 1, mid + 1, r, u, v, val);
        t[id] = t[id * 2] + t[id * 2 + 1];
 
    }
public : 
    void init(ll n, vector<ll> &a){
        t.resize(4 * n + 1, 0);
        lazy.resize(4 * n + 1, 0);
        build(1, 1, n, a);
    }
    ll get_sum(ll u, ll v, ll n){
        return get(1, 1, n, u, v);
    }
    void update_query(ll u, ll v, ll val){
        update(1, 1, n, u, v, val);
    }
 
};
 
void input() {
    cin >> n >> q;
    a.resize(n + 1);
    for (int i = 1;i <= n;++i){
        cin >> a[i];
    }
    SegmentTree st;
    st.init(n, a);
    while (q--)
    {
        ll type, l, r;
        cin >> type;
        if (type == 1){
            ll x;
            cin >> l >> r >> x;
          
            st.update_query(l, r, x);
        }
        if (type == 2){
            cin >> l >> r;
            cout << st.get_sum(l, r, n) << '\n';   
        }
        /* code */
    }
    
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    input();
    return 0;
}
