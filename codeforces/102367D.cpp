#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i=0; i<n;i++)
#define REP1(i,n) for(int i=1; i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
#define IOS()
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...t){cerr<<x<<", ";_do(t...);}
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif

const int MAXN = 100005;

struct Modify {
    short wei, t;
};
vector<Modify> modify;


struct Edge {
	int u, v, w;
};
vector<Edge> edge;

struct Query {
	int u, v, t, id;
};
vector<Query> query;

vector<int> edg[MAXN];

int n, q, dep[MAXN], in[MAXN], sz[MAXN], tp[MAXN], ft[MAXN], son[MAXN];
int ans[MAXN];

void dfs_pre (int nd, int par) {
	sz[nd] = 1;
	dep[nd] = dep[par] + 1;
	ft[nd] = par;
	son[nd] = 0;

	for (auto v : edg[nd]) {
		if (v != par) {
			dfs_pre(v, nd);
			if (sz[v] > sz[son[nd]]) {
				son[nd] = v;
			}
			sz[nd] += sz[v];
		}
	}
}

int tme;
void dfs_hld (int nd, int hd) {
	tp[nd] = hd;
	in[nd] = tme++;

	if (son[nd] != 0) {
		dfs_hld(son[nd], hd);
	}
	for (auto v : edg[nd]) {
		if (v != ft[nd] && v != son[nd]) {
			dfs_hld(v, v);
		}
	}
}

int bit[MAXN];

void add (int x, int val) {
	for (x++;x<MAXN; x+=-x&x) {
		bit[x] += val;
	}
}

int qry (int x) {
	int ret = 0;
	for (x++;x>0; x-=-x&x) {
		ret += bit[x];
	}
	return ret;
}

int qry (int l, int r) {
	return qry(r) - qry(l-1);
}

int qpath (int u, int v) {
	int ret = 0;
	while (tp[u] != tp[v]) {
		if (dep[tp[u]] > dep[tp[v]]) {
			swap(u, v);
		}
		ret += qry(in[tp[v]], in[v]);
		v = ft[tp[v]];
	}
	if(dep[u] > dep[v]) {
		swap(u, v);
	}
	return ret + qry(in[u]+1, in[v]);
}

vector<int> wei[20001];

int edg_lst[MAXN], edg_wei[MAXN];
/**************GOOD*LUCK****************/
int main () {
	IOS();

	cin >> n >> q;
	REP (i, n-1) {
		int u, v, w;
		cin >> u >> v >> w;
		w--;
		edg[u].emplace_back(v);
		edg[v].emplace_back(u);
		edge.push_back({u, v, w});
	}

	dfs_pre(1, 1);
	dfs_hld(1, 1);

	REP1 (b, 20000) {
		for (int i=1, j; i<=20001; i=j+1) {
			modify.push_back({b, i});
			if (b / i == 0) {
				break;
			}
			j = b/(b/i);
		}
	}
	for (auto &E : edge) {
		if (dep[E.u] < dep[E.v]) {
			swap(E.u, E.v);
		}
        edg_wei[in[E.u]] = E.w;
        wei[E.w].emplace_back(in[E.u]);
	}

	REP (i, q) {
		int u, v, t;
		cin >> u >> v >> t;
		query.push_back({u, v, t, i});
	}

	sort(query.begin(), query.end(), [](Query &q1, Query &q2) {
		return q1.t < q2.t;
	});

	sort(modify.begin(), modify.end(), [](Modify &q1, Modify &q2) {
		return q1.t < q2.t;
	});

	#ifdef BTCd
	REP1 (i, n) {
		cout << in[i] << " \n"[i==n];
	}
	#endif
	int idx = 0;

	REP (i, n) {
		add(i, 1);
	}
	for (auto &Q : query) {
		debug(Q.id);
		while (idx < SZ(modify) && modify[idx].t <= Q.t) {
            for (auto eid : wei[modify[idx].wei]) {
                debug(eid, modify[idx].wei, modify[idx].t);
                int cur = modify[idx].wei/modify[idx].t;
                add(eid, cur-edg_lst[eid]);
                edg_lst[eid] = cur;
                debug(eid, cur);
            }
			idx++;
		}

		if (Q.u == Q.v) {
			ans[Q.id] = 1;
		} else {
			ans[Q.id] = qpath(Q.u, Q.v) + 1;
		}
	}

	REP (i, q) {
		cout << ans[i] << endl;
	}
	return 0;
}

/*
5 3
1 2 3
2 3 5
3 4 7
4 5 9
1 5 4
1 5 5
1 4 1

*/
