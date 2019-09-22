#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, m, w[MAXN], s;
ll sum[MAXN], ans, mx;
vector<int> edge[MAXN];
vector<int> bridge[MAXN];

int ccid[MAXN], ccnt, csz[MAXN];
vector<int> stk;
int low[MAXN], dfn[MAXN], ts;
void bcc (int nd, int par) {
    dfn[nd] = low[nd] = ts++;
    stk.emplace_back(nd);
    for (auto v : edge[nd]) {
        if (v != par) {
            if (dfn[v] == -1) {
                bcc(v, nd);
                low[nd] = min(low[nd], low[v]);
            } else {
                low[nd] = min(low[nd], dfn[v]);
            }
        }
    }

    if (nd == par || low[nd] == dfn[nd]) {
        ccnt++;
        while (stk.back() != nd) {
            ccid[stk.back()] = ccnt;
            csz[ccnt]++;
            stk.pop_back();
        }
        ccid[stk.back()] = ccnt;
        csz[ccnt]++;
        stk.pop_back();
    }
}

int sz[MAXN];
void build_sz (int nd, int par) {
    sz[nd] += csz[nd] > 1;
    for (auto v : bridge[nd]) {
        if (v != par) {
            build_sz(v, nd);
            sz[nd] += sz[v];
        }
    }
}

ll prun (int nd, int par) {
    ll ret = 0;
    for (auto v : bridge[nd]) {
        if (v != par) {
            ret = max(ret, prun(v, nd));
        }
    }
    return ret + sum[nd];
}

ll dfs (int nd, int par) {
    ll ret = sum[nd];
    for (auto v : bridge[nd]) {
        if (v != par) {
            if (sz[v] > 0) {
                ret += dfs(v, nd);
            } else {
                mx = max(mx, prun(v, nd));
            }
        }
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP1 (i, n) {
        cin >> w[i];
    }
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }
    cin >> s;

    memset(dfn, -1, sizeof(dfn));
    bcc(s, s);

    REP1 (i, n) {
        sum[ccid[i]] += w[i];
        for (auto v : edge[i]) {
            if (ccid[i] != ccid[v]) {
                bridge[ccid[i]].emplace_back(ccid[v]);
            }
        }
    }

    REP1 (i, ccnt) {
        sort(bridge[i].begin(), bridge[i].end());
        bridge[i].resize(unique(bridge[i].begin(), bridge[i].end()) - bridge[i].begin());
    }

    int sid = ccid[s];
    build_sz(sid, sid);
    dfs(sid, sid);

    ans = dfs(sid, sid);
    cout << ans + mx << endl;
    return 0;
}
