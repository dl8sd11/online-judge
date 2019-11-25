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
#define pary(a,n) for(int i=0;i<n;i++){cout<<a[i]<<" ";}cout<<endl;
#else
#define pary(a,n)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

int n;
int deq[MAXN], sz;
vector<pair<int,ll> > edge[MAXN];
ll S[MAXN], V[MAXN], dp[MAXN], dis[MAXN];

void add_edge(int u, int v, int d) {
    edge[u].emplace_back(v, d);
    edge[v].emplace_back(u, d);
}

// dp[nd] = dp[x] + dep[nd]*V[nd] - dep[x]*V[nd] + S[nd]
long double getIntersection(int i, int j) {
    return (long double)(dp[j]-dp[i])/(dis[i]-dis[j]);
}

int getEnd(int nd) {
    int l = 0, r = sz;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (getIntersection(deq[mid-1], nd) >= getIntersection(deq[mid-1], deq[mid])) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}

ll calc(ll x, int id) {
    return dp[id] + x*dis[id];
}

ll eval(ll x) {
    int l = 0, r = sz;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (getIntersection(deq[mid-1], deq[mid]) >= x) {
            l = mid;
        } else {
            r = mid;
        }
    }

    debug(calc(x, deq[sz-1]), deq[l], l);
    return min({calc(x, deq[0]), calc(x, deq[sz-1]), calc(x, deq[l])});
}

void dfs(int nd, int par) {
    if (nd != 1) {
        dp[nd] = eval(-V[nd])+dis[nd]*V[nd]+S[nd];

        debug(nd, dp[nd], sz);
        pary(deq, sz);
    }
    int endpt = getEnd(nd);
    debug(endpt);
    int csz = sz, clst = deq[endpt];
    deq[endpt] = nd;
    sz = endpt + 1;

    for (auto v : edge[nd]) {
        if (v.first != par) {
            dis[v.first] = dis[nd] + v.second;
            dfs(v.first, nd);
        }
    }

    sz = csz, deq[endpt] = clst;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n-1) {
        int u, v, d;
        cin >> u >> v >> d;
        add_edge(u, v, d);
    }
    for (int i=2; i<=n; i++) {
        cin >> S[i] >> V[i];
    }

    dfs(1, 0);

    for (int i=2; i<=n; i++) {
        cout << dp[i] << " \n"[i==n];
    }
}
/*
5
1 2 20
2 3 12
2 4 1
4 5 3
26 9
1 10
500 2
2 30
*/
