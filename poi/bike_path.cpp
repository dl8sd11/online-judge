#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, cc[MAXN], ccnt;
vector<int> edge[MAXN], rev[MAXN], dag[MAXN];

bool vis[MAXN];
int ans[MAXN], dp[MAXN];

vector<int> topo;
void dfs1 (int nd) {
    vis[nd] = true;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    topo.emplace_back(nd);
}

void dfs2 (int nd) {
    vis[nd] = false;
    cc[nd] = ccnt;
    dp[ccnt]++;
    for (auto v : rev[nd]) {
        if (vis[v]) {
            dfs2(v);
        }
    }
}

bool vs[MAXN];
void solve (int nd) {
    if (vs[nd]) {
        return;
    }
    vs[nd] = true;

    for (auto v : dag[nd]) {
        solve(v);
        dp[nd] += dp[v];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        rev[v].emplace_back(u);
    }

    REP1 (i, n) {
        if (!vis[i]) {
            dfs1(i);
        }
    }

    reverse(topo.begin(),topo.end());
    for (auto v : topo) {
        if (vis[v]) {
            dfs2(v);
            ccnt++;
        }
    }

    REP1 (i, n) {
        for (auto v : edge[i]) {
            if (cc[v] != cc[i]) {
                dag[cc[i]].emplace_back(cc[v]);
            }
        }
    }
    REP (i, ccnt) {
        solve(i);
    }

    REP1 (i, n) {
        cout << dp[cc[i]] - 1 << endl;
    }
}
