#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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

const int MAXN = 500005;
const ll MOD = 1000000007;

int n, m;
vector<int> oG[MAXN], rG[MAXN];

bool vis[MAXN];
vector<int> topo;
vector<vector<int> > cc;
int ccid[MAXN];

void dfs1 (int nd) {
    vis[nd] = true;

    for (auto v : oG[nd]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    topo.eb(nd);
}

void dfs2 (int nd) {
    vis[nd] = false;

    ccid[nd] = cc.size() - 1;
    cc.back().eb(nd);
    for (auto v : rG[nd]) {
        if (vis[v]) {
            dfs2(v);
        }
    }
}

int sz[MAXN];
int dp[MAXN], fw[MAXN], bw[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    for (int i=0; i<m; i++) {
        int f, t;
        cin >> f >> t;
        oG[f].eb(t);
        rG[t].eb(f);
    }

    for (int i=1; i<=n; i++) {
        if (!vis[i]) {
            dfs1(i);
        }
    }

    assert(SZ(topo) == n);
    for (int i=n-1; i>=0; i--) {
        int x = topo[i];
        if (vis[x]) {
            cc.eb();
            dfs2(x);
        }
    }

    debug(cc);

    memset(fw, 0x3f, sizeof(fw));
    memset(bw, -1, sizeof(bw));

    for (int i=1; i<=n; i++) {
        for (auto v : oG[i]) {
            if (ccid[v] != ccid[i]) {
                bw[ccid[v]] = max(bw[ccid[v]], ccid[i]);
                fw[ccid[i]] = min(fw[ccid[i]], ccid[v]);
            }
        }
    }

    memset(dp, 0, sizeof(dp));
    for (int i=0; i<SZ(cc); i++) {
        sz[i] += dp[i];
        dp[i]++;
        if (fw[i] < SZ(cc)) {
            dp[fw[i]] += dp[i];
        }
    }

    memset(dp, 0, sizeof(dp));
    for (int i=SZ(cc)-1; i>=0; i--) {
        sz[i] += dp[i];
        dp[i]++;
        if (bw[i] >= 0) {
            dp[bw[i]] += dp[i];
        }
    }

    vector<int> ans;
    for (int i=0; i<SZ(cc); i++) {
        if (sz[i] == SZ(cc) - 1) {
            for (auto c : cc[i]) {
                ans.eb(c);
            }
        }
    }
    sort(ALL(ans));

    cout << SZ(ans) << endl;
    for (int i=0; i<SZ(ans); i++) {
        cout << ans[i] << " \n"[i==SZ(ans)-1];
    }

}

