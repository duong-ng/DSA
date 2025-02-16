#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <stack>
#include <unordered_map>
#define ll long long
#define f first
#define pll pair<long long, long long> 
#define s second
#define pb push_back
#define lcm(i1, i2) i1 *i2 / __gcd(i1, i2)
using namespace std;
const int maxN = int(1e6) + 7;
const ll INF = 1e18;
const ll MOD = (long long) 1e9 + 7;
const char nl = '\n';

string st;
ll t, n, m, lg, cnt = 0;
ll pre[maxN];
map<ll,ll> mp;
vector<pll> inp, hull;



long double Spolygon(vector<pll> p){
	ll ans = 0;
	ll pn = p.size();
	for (int i = 0;i < p.size();++i){
		ll j = (i + 1) % pn;
		ans += (long long)p[i].s * p[j].f - (long long)p[i].f * p[j].s;
	}
	long double res = (long double)abs(ans) / 2.0; 
	return res;
}

ll ccw(pll p1, pll p2, pll p3){
	ll x1 = p1.f;
	ll y1 = p1.s;
	ll x2 = p2.f;
	ll y2 = p2.s;
	ll x3 = p3.f;
	ll y3 = p3.s;
	ll cross = (x2 - x1) * (y1 + y2) + (x3-x2)*(y2 + y3) + (x1 - x3)*(y1 + y3);
	if (cross < 0){
		return 1;
	}
	if (cross > 0){
		return -1;
	}
	else return 0;
}


void solve(){
	hull.pb(inp[0]);
	hull.pb(inp[1]);
	for (int i = 2;i < n;++i){
		auto point = inp[i];
		while (ccw(hull[hull.size() - 2],hull.back(), point) != 1 && hull.size() >= 2){
			hull.pop_back();
		}
		hull.pb(point);
	}
	ll k = hull.size();
	for (int i = n - 2;i >= 0;--i){
		auto point = inp[i];
		while (ccw(hull[hull.size() - 2], hull.back(),point) != 1 && hull.size() > k){
			hull.pop_back();
		}
		hull.pb(point);
	}
	hull.pop_back();
	cout<< hull.size() << '\n';
    cout << fixed << setprecision(1) << Spolygon(hull) << endl; 
    int start = 0;
    for (int i = 1; i < hull.size(); ++i) {
        if (hull[i].second < hull[start].second || 
            (hull[i].second == hull[start].second && hull[i].first < hull[start].first)) {
            start=i;
        }
    }
    for (int i = start; i < hull.size(); ++i) {
        cout << hull[i].first << " " << hull[i].second << '\n';
    }
    for (int i = 0; i < start; ++i) {
        cout << hull[i].first << " " << hull[i].second << '\n';
    }
	
}


void input(){
	cin >> n;
	for (int i = 0;i < n;++i){
		ll x, y; cin >> x >> y;
		inp.pb({x, y});
	}	
	sort(inp.begin(), inp.end());
	solve();
}


int main(){
//	freopen("testing.inp", "r", stdin);
//	freopen("testing.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	input();
	return 0;
}
