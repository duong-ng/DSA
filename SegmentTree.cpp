#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <climits>
#include <map>
#include <numeric>
#include <algorithm>
#include <cstring>
#define int long long 
#define f first
#define s second
#define pll pair<long long,long long>
#define lcm(i1, i2) i1 *i2 / __gcd(i1, i2)
#define min3(i1, i2, i3) min(i1, min(i2, i3))
#define pb push_back
using namespace std;
const int maxN = 3e6 + 6;
const char nl = '\n';
int n, q, m, k;
vector<int> a(maxN);
 
 
class SegmentTree{
private : 
	vector<int> t;
	void build(int id, int l, int r, vector<int> &a){
		if (l == r){ // base case
			t[id] = a[l];
		//	cout << id << ' ' << l << ' ' << r << ' ' << t[id] << nl; 
			return;
		}
		int mid = (l + r) >> 1; //break the array into subsegment
		build(id * 2, l, mid, a); // compute left node
		build(id * 2 + 1,mid + 1, r, a); // compute right node
	
		t[id] = min(t[id * 2], t[id * 2 + 1]); 
	//	cout << id << ' ' << l << ' ' << r  <<' ' << t[id] << nl; 
	}
	int get_min(int id, int l, int r, int u , int v){
		if (u > r || l > v) return INT_MAX;
		if (u <= l && r <= v){
			return t[id];
		}
		int mid = (l + r) >> 1;
		int t1 = get_min(id * 2,l, mid,u, v);
		int t2 = get_min(id * 2 + 1, mid + 1, r, u, v);
		return min(t1, t2);
	}
	void update(int id, int l, int r, int pos, int val){
		if (pos < l || pos > r) return;
		if (l == r && r == pos){
			t[id] = val;
			return;
		}
		int mid = (l + r) >> 1;
		update(id * 2, l, mid, pos, val);
		update(id * 2 + 1, mid + 1, r, pos, val);
		
		t[id] = min(t[id * 2], t[id * 2 + 1]); 
	} 
public : 
	void init(int n, vector<int> &a){
		t.resize(4 * n + 1);
		build(1, 1, n, a);
	}
	int get_min(int u, int v, int n){
		return get_min(1, 1, n, u, v);
	}
	void update_point(int u, int v, int n){
		update(1, 1, n, u, v);
	}
};
 
 
void input(){
	cin >> n >> q;
	a.resize(n + 1);
	for (int i = 1;i <= n;++i){
		cin >> a[i];
	}
	SegmentTree st;
	st.init(n, a);
	while (q--)
	{
		int type, l, r;
		cin >> type >> l >> r;
		if (type == 1){
			st.update_point(l, r, n);
		}
		else {
			cout << st.get_min(l, r, n) << '\n';
		}
		/* code */
	}
	

}
 
	
signed main(){
//	freopen("BIT.inp","r",stdin);
//	freopen("BIT.out","w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    input();
    return 0;
}
