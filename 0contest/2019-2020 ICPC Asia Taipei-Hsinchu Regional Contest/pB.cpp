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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"{"<<v.X<<","<<v.Y<<"}";}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1000005;
const int MOD = 1000000007;

int n, dp[MAXN][3]; // [null, one, full]
vector<int> edge[MAXN];

void cfull (pii &dfull, int dl, int nd) {
    int df = dfull.X == -1 ? -MOD : dp[dfull.X][1] - dp[dfull.X][2];
    int ds = dfull.Y == -1 ? -MOD : dp[dfull.Y][1] - dp[dfull.Y][2];

    if (dl > df) {
        dfull.Y = dfull.X;
        dfull.X = nd;
    } else if (dl > ds) {
        dfull.Y = nd;
    }
}

void cnull (pii &dnull, int dl, int nd) {
    int df = dnull.X == -1 ? -MOD : dp[dnull.X][1] - dp[dnull.X][0];
    int ds = dnull.Y == -1 ? -MOD : dp[dnull.Y][1] - dp[dnull.Y][0];

    if (dl > df) {
        dnull.Y = dnull.X;
        dnull.X = nd;
    } else if (dl > ds) {
        dnull.Y = nd;
    }
}


void dfs (int nd, int par) {

    int aone = 0, amin = 0, cnt = 0;
    pair<int,int> dfull = {-1, -1}, dnull = {-1, -1};

    for (auto v : edge[nd]) {
        if (v != par) {
            cnt++;
            dfs(v, nd);
            amin += dp[v][0];
            aone += dp[v][1];

            int df = dp[v][1] - dp[v][2];
            int dn = dp[v][1] - dp[v][0];
            cfull(dfull, df, v);
            cnull(dnull, dn, v);

//            debug(nd, v, dfull);
        }
    }
//    debug(nd, dfull, dnull, aone, amin, cnt);
    if (cnt == 0) {
        dp[nd][2] = dp[nd][1] = 1;
    } else {
        dp[nd][2] = min(1 + amin, aone - dp[dfull.X][1] + dp[dfull.X][2]);

        if (cnt == 1) {
            dp[nd][1] = dp[nd][2];
//        } else if (cnt == 2) {
//            dp[nd][1] = min(aone - dp[dnull.X][1] + dp[dnull.X][0], dp[nd][2]);
        } else {
            int mx = -MAXN;
            if (dfull.X == dnull.X) {
                mx = max(mx, dp[dfull.X][1] - dp[dfull.X][2] + dp[dnull.Y][1] - dp[dnull.Y][0]);
                mx = max(mx, dp[dfull.Y][1] - dp[dfull.Y][2] + dp[dnull.X][1] - dp[dnull.X][0]);
            } else {
                mx = dp[dfull.X][1] - dp[dfull.X][2] + dp[dnull.X][1] - dp[dnull.X][0];
            }
            dp[nd][1] = min(aone - mx, dp[nd][2]);
        }

        // change
        dp[nd][0] = min(aone - dp[dnull.X][1] + dp[dnull.X][0], dp[nd][1]);
    }

    assert(dp[nd][0] <= dp[nd][1] && dp[nd][1] <= dp[nd][2]);

//    debug(nd, par, dp[nd][0], dp[nd][1], dp[nd][2]);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    srand(time(0));

    while (cin >> n) {
        memset(dp, 0, sizeof(dp));

        REP (i, n-1) {
            int u, v;
            cin >> u >> v;
            edge[u].eb(v);
            edge[v].eb(u);
        }

        int root = rand() % n + 1;
        debug(root);
        dfs(root, -1);

        REP1 (i, n) {
            edge[i].clear();
        }

        cout << dp[root][1] << endl;
    }
}
