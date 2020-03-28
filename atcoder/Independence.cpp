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
template<typename T> ostream &operator << (ostream &os,array<T,2> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 702;
const ll MOD = 1000000007;

int n, m;
bool edge[MAXN][MAXN];

vector<array<int, 2> > comp;

bool vis[MAXN], cl[MAXN];
void dfs (int nd, array<int,2> &cnt, bool c) {
    debug(nd, c);
    vis[nd] = true;
    cl[nd] = c;
    cnt[c]++;

    REP1 (i, n) {
        if (edge[nd][i]) {
            if (vis[i]) {
                if (cl[nd] == cl[i]) {
                    debug(i, nd);
                    cout << -1 << endl;
                    exit(0);
                }
            } else {
                    dfs(i, cnt, !c);
            }
        }
    }
}

bool dp[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    REP1 (i, n) {
        REP1 (j, n) {
            if (i != j) {
                edge[i][j] = true;
            }
        }
    }
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u][v] = false;
        edge[v][u] = false;
    }

    REP1 (i, n) {
        if (!vis[i]) {
            debug(i);
            array<int,2> cur = {0, 0};
            dfs(i, cur, 0);

            comp.eb(cur);
        }
    }

    debug(comp);
    dp[0] = true;
    for (auto ar : comp) {
        for (int i=MAXN-1;i>=0;i--) {
            dp[i] = (i>=ar[0]?dp[i-ar[0]]:0) | (i>=ar[1]?dp[i-ar[1]]:0);
        }
    }

    auto cob = [](int x) {
        return x * (x-1) / 2;
    };

    int ans = MOD;
    REP (i, n+1) {
        if (dp[i]) {
            assert(dp[n-i]);
            ans = min(ans, cob(i) + cob(n-i));
        }
    }

    cout << ans << endl;
}
