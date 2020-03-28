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

int n, k, sz[MAXN];
bool dp[MAXN];
vector<int> edge[MAXN];

void build_sz (int nd) {
    sz[nd] = 1;
    for  (auto v : edge[nd]) {
        build_sz(v);
        sz[nd] += sz[v];
    }
}

int dfs_ans (int nd, double lim) {
    if (edge[nd].empty()) {
        dp[nd] = true;
        return 1;
    } else {
        int ret = 1;
        dp[nd] = false;
        for (auto v : edge[nd]) {
            ret = max(ret, dfs_ans(v, lim));

            if (dp[v]) {
                double frac = double(sz[v]) / (sz[nd]-1);
                if (frac >= lim) {
                    dp[nd] = true;
                    ret = sz[nd];
                }
            }
        }
        return ret;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n-1) {
        int p, v = i + 2;
        cin >> p;
        edge[p].eb(v);
    }

    build_sz(1);
    pary(sz+1,sz+n+1);

    double l = 0, r = 1;
    const double eps = 1e-9;

    while (l < r - eps) {
        double m = (l + r) / 2;

        double res = dfs_ans(1, m);
//        debug(m, res);

        if (res > k) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << fixed << setprecision(8) << r << endl;
}
