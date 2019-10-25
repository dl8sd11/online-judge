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

int n;
ll x[MAXN], ans;
vector<int> edge[MAXN];

ll mgcd(ll a, ll b) {
    if (a == 0 || b == 0) {
        return a ? a : b;
    } else {
        return __gcd(a, b);
    }
}
void dfs (int nd, int par, map<ll,int> mp) {
    map<ll, int> cmap;
    cmap[x[nd]] = 1;
    (ans += x[nd]) %= MOD;
    for (const auto &p : mp) {
        debug(nd, p.first, p.second);
        ll nw = mgcd(x[nd], p.first);
        (ans += nw * p.second % MOD) %= MOD;
        cmap[nw] += p.second;
    }


    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd, cmap);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> x[i];
    }
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }


    dfs(1, 1, {});

    cout << ans << endl;
    return 0;
}
