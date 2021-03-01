#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
#define F first
#define S second
#define eb emplace_back
vector<pll> vec1, vec2;
ll n, m;
void build1() {
	sort(vec1.begin(), vec1.end());
	vector<pll> tmp;
	for(int i = 0; i < n; ++ i) {
		if(tmp.size() && tmp.back().F == vec1[i].F) {
			tmp.back().S = vec1[i].S;
			continue;
		}
		if(tmp.size() && tmp.back().S >= vec1[i].S)
			continue;
		tmp.eb(vec1[i]);
	}
	vec1 = tmp;
	n = vec1.size();
}
void build2() {
	sort(vec2.begin(), vec2.end());
	vector<pll> tmp;
	for(int i = 0; i < m; ++ i) {
		while(tmp.size() && tmp.back().S >= vec2[i].S)
			tmp.pop_back();
		tmp.eb(vec2[i]);
	}
	vec2 = tmp;
	m = vec2.size();
}
int main() {
	ios_base::sync_with_stdio(0);	cin.tie(0);
	cin >> n >> m;
	vec1.resize(n);
	vec2.resize(m);
	for(int i = 0; i < n; ++ i) {
		cin >> vec1[i].S >> vec1[i].F;
		vec1[i].S = - vec1[i].S;
	}
	for(int i = 0 ; i < m; ++ i ){
		cin >> vec2[i].S >> vec2[i].F;
		vec2[i].S = - vec2[i].S;
	}
	build1();
	build2();
	// cerr << "n=" << n << '\n';
	// for(int i = 0; i < n; ++ i){
	// 	cout << vec1[i].F << ' ' << vec1[i].S << '\n';
	// }
	// cerr << "m=" << m << '\n';
	// for(int i = 0; i < m; ++ i){
	// 	cout << vec2[i].F << ' ' << vec2[i].S << '\n';
	// }
	int l = 0, r;
	while(l < m && vec2[l].F <= vec1[0].F ) ++ l;
	r = l;
	while(r < m && vec2[r].S <= vec1[0].S) ++ r;
	ll ans = 0;
	int pre = l;
	for(int i = 0; i < n; ++ i) {
		l = pre;
		while(l < m && vec2[l].F <= vec1[i].F ) ++ l;
		while(r < m && vec2[r].S <= vec1[i].S) ++ r;
		// l = max(l, pre);
		pll ma = pll(-1, pre);
		for(int j = l; j < min((ll)r, ma.S + 200); ++ j) {
			ll tmp = (vec2[j].F - vec1[i].F) * (vec1[i].S - vec2[j].S);
			ma = max(ma, pll(tmp, j));
		}
		for(int j = r - 1; j >= max(l, r - 200); -- j) {
			ll tmp = (vec2[j].F - vec1[i].F) * (vec1[i].S - vec2[j].S);
			ma = max(ma, pll(tmp, j));	
		}
		ans = max(ans, ma.F);
		pre = ma.S;
	}
	cout << ans << '\n';
}
