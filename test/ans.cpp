#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb emplace_back
const int maxn = 100010, maxk = 101;
const ll inf = 1ll << 55;
int n, v, p[maxn];
vector<int> edge[maxn];
ll dp[2][4][maxk][maxn], sum[maxn];
ll res;
void dfs(int now, int last = 0) {
	for (int j : {0, 1}) for (int k = 0;k < 3;++k) for (int i = 0;i <= v;++i) {
		auto &val = dp[j][k][i][now];
		val = 0;
	}

	for (int u : edge[now]) if (u != last) {
		dfs(u, now);
if (false) for (int j : {0, 1}) for (int k = 0;k < 3;++k) for (int i = 0;i <= v;++i) {
			auto &val = dp[j][k][i][now];
			if (k == 0)
				res = max(res, val + max({
						dp[j^1][0][v-i][u],
						dp[j^1][1][v-i][u],
						dp[j^1][2][v-i][u]}));
			if (k == 1)
				res = max(res, val + max({
						dp[j^1][0][v-i][u],
						dp[j^1][1][v-i][u],
						dp[j^1][2][v-i][u] - p[now]}));
			if (k == 2)
				res = max(res, val + max({
						dp[j^1][0][v-i][u],
						dp[j^1][1][v-i][u] - p[u],
						dp[j^1][2][v-i][u] - (j==0?p[u] : p[now])}));
		}
		for (int j : {0, 1}) for (int k = 0;k < 3;++k) for (int i = 0;i <= v;++i) {
			auto &val = dp[j][k][i][now];
			if (k == 0)
				val = max({val, dp[j][0][i][u], dp[j][1][i][u]});
			if (k == 1)
				val = max(val, dp[j][2][i][u]);
			if (k == 2 && i) 
				val = max({val, dp[j][0][i-1][u] + sum[now], 
						dp[j][1][i-1][u] + sum[now] - p[u],
						dp[j][2][i-1][u] + sum[now] - (j==0?p[now]:p[u])}) ;
			res = max(res, val);
		}
	}
	res = max(res, sum[now]);
	for (int j : {0, 1})  for (int i = 1;i <= v;++i) {
		auto &val = dp[j][2][i][now];
		val = max(val, sum[now]);
	}
}

signed main () {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> v;
	if (v == 0) return cout << 0 << '\n', 0;
	for (int i = 1;i <= n;++i)
		cin >> p[i];
	for (int a, b, i = 1;i < n;++i) {
		cin >> a >> b;
		edge[a].pb(b);
		edge[b].pb(a);
		sum[a] += p[b];
		sum[b] += p[a];
	}
	for (int i = 1;i <= n;++i)
		dfs(i);
	cout << res << '\n';
}
