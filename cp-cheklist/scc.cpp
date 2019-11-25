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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, m, c[MAXN], ccid[MAXN], ccnt;
vector<vector<int> > scc;

vector<int> edg[MAXN], rev[MAXN], topo;
bool vis[MAXN];

void add_edge (int f, int t) {
    edg[f].emplace_back(t);
    rev[t].emplace_back(f);
}

void dfs1 (int nd) {
    vis[nd] = true;
    for (auto v : edg[nd]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    topo.emplace_back(nd);
}

void dfs2 (int nd, vector<int> &cur) {
    vis[nd] = false;
    cur.emplace_back(nd);
    ccid[nd] = ccnt;
    for (auto v : rev[nd]) {
        if (vis[v]) {
            dfs2(v, cur);
        }
    }
}

void build_scc () {
    REP1 (i, n) {
        if (!vis[i]) {
            dfs1(i);
        }
    }

    for (int i=n-1; i>=0; i--) {
        int x = topo[i];
        if (vis[x]) {
            vector<int> cur;
            dfs2(x, cur);
            scc.emplace_back(cur);
            ccnt++;
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;
    REP1 (i, n) {
        cin >> c[i];
    }
    cin >> m;
    REP (i, m) {
        int f, t;
        cin >> f >> t;
        add_edge(f, t);
    }

    build_scc();

    ll ans = 1;
    ll sum = 0;

    int idx = 0;
    for (auto cc : scc) {
        int mn = 0x3f3f3f3f, cnt = 0;
        idx++;
        for (auto v : cc) {
            debug(v, idx);
            if (c[v] < mn) {
                cnt = 1;
                mn = c[v];
            } else if (c[v] == mn){
                cnt++;
            }
        }
        ans = ans * cnt % MOD;
        sum += mn;
    }

    cout << sum << " " << ans << endl;
}
