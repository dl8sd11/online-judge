#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)

const ll MAXN = 1003;

ll n,m,cc;
char cp[MAXN][MAXN];

ll par[MAXN*2],sz[MAXN*2];

void init(ll N) {
    cc = N;
    REP (i,N+3) {
        par[i] = i;
        sz[i] = 1;
    }
}
ll fnd(ll x) {
    return x == par[x] ? x : (par[x] = fnd(par[x]));
}

void uni(ll x,ll y) {
    if (sz[x=fnd(x)] < sz[y=fnd(y)]) {
        swap(x,y);
    }
    if (x == y) {
        return;
    }
    cc--;
    par[y] = x;
    sz[x] += sz[y];
}

vector<ll> edge[MAXN*2];
ll dp[MAXN*2],deg[MAXN*2];
vector<ll> topo;
/********** Good Luck :) **********/
int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n >> m;
    init(n+m);

    REP (i,n) {
        REP (j,m) {
            cin >> cp[i][j];
            if (cp[i][j] == '=') {
                uni(i,j+n);
            }
        }
    }

    REP (i,n) {
        REP (j,m) {
            if (cp[i][j] != '=') {
                ll x = fnd(i),y = fnd(j+n);
                if (cp[i][j] == '>') {
                    edge[x].emplace_back(y);
                    deg[y]++;
                } else {
                    edge[y].emplace_back(x);
                    deg[x]++;
                }
            }
        }
    }

    vector<ll> stk;
    REP (i,n+m) {
        if (i == fnd(i)) {
            if (deg[i] == 0) {
                stk.emplace_back(i);
            }
        }
    }

    while (stk.size()) {
        ll cur = stk.back();
        stk.pop_back();

        topo.emplace_back(cur);
        for (auto v : edge[cur]) {
            if (--deg[v] == 0) {
                stk.push_back(v);
            }
        }
    }

    if (SZ(topo) != cc) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;

    RREP (i,cc-1) {
        dp[topo[i]] = 1;
        for (auto v : edge[topo[i]]) {
            dp[topo[i]] = max(dp[topo[i]],dp[v]+1);
        }
    }

    REP (i,n) {
        cout << dp[fnd(i)] << " \n"[i==n-1];
    }
    REP (i,m) {
        cout << dp[fnd(i+n)] << " \n"[i==m-1];
    }
    return 0;
}
