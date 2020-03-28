#include "split.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef tmd
#define debug(...) fprintf(stderr,"%d (%s) = ",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do (T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream &printRng (IT bg, IT ed, ostream &os) {
    os<<"{";
    for (IT it=bg; it!=ed; it++) {
        if (it!=bg) {
            os<<",";
        }
        os<<(*it);
    }
    return os<<"}";
}
template<typename T> ostream &operator << (ostream &os, vector<T> &vec) {
    return printRng(vec.begin(), vec.end(), os);
}
#else
#define debug(...)
#endif // tmd

const int MAXN = 100005;
const int MAXM = 200005;

vector<int> edge[MAXN], tree[MAXN], btree[MAXN];
vector<pair<int,int> > gp;

bool vis[MAXN];
int sz[MAXN];

int N;

pair<int,int> msplit = {1, MAXN+1};

void span (int nd) {
    vis[nd] = true;
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            span(v);
            sz[nd] += sz[v];
            debug(v, nd);
            tree[nd].emplace_back(v);

            btree[nd].emplace_back(v);
            btree[v].emplace_back(nd);

            int cur = min(sz[v], N-sz[v]);
            if (cur >= gp[0].first && cur < msplit.second) {
                msplit = {v, cur};
            }
        }
    }
}

void build (int nd, vector<int> &res) {
    res.emplace_back(nd);
    debug(nd);
    for (auto v : tree[nd]) {
        build(v, res);
    }
}

vector<int> inv (const vector<int> &s) {
    memset(vis, 0, sizeof(vis));
    for (const auto v : s) {
        vis[v] = true;
    }
    vector<int> res;
    for (int i=0; i<N; i++) {
        if (!vis[i]) {
            res.emplace_back(i);
        }
    }
    return res;
}

bool inSet[MAXN];
void dfsN (int nd, int par, vector<int> &res, int &cnt, int g) {
    if (cnt < g) {
        cnt++;
        res.emplace_back(nd);
        for (auto v : btree[nd]) {
            if (v != par && inSet[v]) {
                dfsN(v, nd, res, cnt, g);
            }
        }
    }
}

vector<int> trim (const vector<int> &s, int g) {
    memset(inSet, 0, sizeof(inSet));
    for (auto v : s) {
        inSet[v] = true;
    }
    vector<int> ret;
    int cnt = 0;
    dfsN(s.front(), -1, ret, cnt, g);
    return ret;
}

vector<int> find_split(int n, int a, int b, int c, vector<int> p, vector<int> q) {
    N = n;
	gp = {{a,1}, {b,2}, {c,3}};
	sort(gp.begin(), gp.end());

    int m = p.size();
    for (int i=0; i<m; i++) {
        int u = p[i];
        int v = q[i];
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    span(0);
    debug(msplit.first, msplit.second);

    vector<int> aset;
    build(msplit.first, aset);
    vector<int> bset = inv(aset);

    if (aset.size() > bset.size()) {
        swap(aset, bset);
    }

    if (aset.size() < gp[0].first || bset.size() < gp[1].first) {
        vector<int> fail(n, 0);
        return fail;
    }

    debug(aset);
    debug(bset);

    aset = trim(aset,gp[0].first);
    bset = trim(bset,gp[1].first);

    vector<int> ret(n, gp[2].second);
    for (auto v : aset) {
        ret[v] = gp[0].second;
    }
    for (auto v : bset) {
        ret[v] = gp[1].second;
    }

	return ret;
}
