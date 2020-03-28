#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define eb emplace_back
#define X first
#define Y second
#define ALL(i) i.begin(),i.end()
#define MEM(i,a) memset(i,(a),sizeof(i))
#ifdef tmd
#define debug(...) fprintf(stderr,"%d(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x) {
    cerr<<x<<endl;
}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {
    cerr<<x<<",";
    _do(y...);
}
template<typename IT> ostream& _print(IT bg, IT ed, ostream &os) {
    for (IT it=bg;it!=ed; it++) {
        if (it==bg) {
            os << "{" << *it;
        } else {
            os << "," << *it;
        }
    }
    return os << "}";
}
template<typename IT> void pary (IT bg, IT ed) {
    _print(bg, ed, cerr);
}
template<typename T> ostream& operator<< (ostream &os, const vector<T> &vec) {
    return _print(vec.begin(), vec.end(),os);
}
#define IOS()
#else
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define pary(...)
#endif // tmd

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 100005;
const int MAXV = 102;

int n, w, p[MAXN];
ll sum[MAXN], dp[MAXN][MAXV];
vector<int> edge[MAXN];

void solve (int nd, int par) {
    REP1 (j, w) {
        dp[nd][j] = 0;
    }
    for (auto v : edge[nd]) {
        if (v != par) {
            solve(v, nd);
            for (int j=1; j<=w; j++) {
                dp[nd][j] = max(dp[nd][j], dp[v][j-1] + sum[nd]-p[par]);
                dp[nd][j] = max(dp[nd][j], dp[v][j]);
            }
        }
    }
}
/*******TommyDong orz*********/
int main () {
    IOS();

    cin >> n >> w;
    REP1 (i, n) {
        cin >> p[i];
    }
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
        sum[u] += p[v];
        sum[v] += p[u];
    }

    ll ans = 0;

    vector<int> leaf = {1};
    for (int i=2; i<=n; i++) {
        if (edge[i].size() == 1) {
            leaf.eb(i);
        }
    }
    random_shuffle(leaf.begin()+1, leaf.end());
    auto tm = clock();

    for (auto i : leaf) {
        auto nw = clock();
        if (double(nw - tm) / CLOCKS_PER_SEC >= 3.5) {
            break;
        }
        solve(i, 0);
        REP1 (j, w) {
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << endl;

    return 0;
}
