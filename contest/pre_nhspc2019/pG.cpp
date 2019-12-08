#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("03","unroll-loops")
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define MEM(a,b) memset(a,(b),sizeof(a))
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d: (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &p){return os<<"("<<p.first<<","<<p.second<<")";}
template<typename IT> ostream &_printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        os << (it==bg?"":",") << *it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &vec) {return _printRng(os, vec.begin(),vec.end());}
template<typename IT> void pary (IT bg, IT ed) {_printRng(cerr,bg,ed);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 500005;

int n, m;
vector<int> edge[MAXN];

bool isCut[MAXN], vis[MAXN];

int dfn[MAXN], low[MAXN], tme;
void dfs (int nd, int par) {
    dfn[nd] = low[nd] = tme++;
    vis[nd] = true;

    bool cc = false;
    int child = 0;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            dfs(v, nd);
            child++;
            if (low[v] >= dfn[nd]) {
                cc = true;
            }
            low[nd] = min(low[nd], low[v]);
        } else {
            low[nd] = min(low[nd], dfn[v]);
        }
    }

    if (nd == par) {
        if (child >=2 ) {
            isCut[nd] = true;
        }
    } else {
        isCut[nd] = cc;
    }
}

int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    REP1 (i, n) {
        if (!vis[i]) {
            dfs(i, i);
        }
    }

    vector<int> ans;
    REP1 (i, n) {
        if (isCut[i]) {
            debug(i);
            int cnt = 0;
            for (auto v : edge[i]) {
                cnt += !isCut[v];
            }

            if (cnt >= 4) {
                ans.emplace_back(i);
            }

        }
    }

    REP (i, SZ(ans)) {
        cout << ans[i] << " \n"[i==SZ(ans)-1];
    }
}
