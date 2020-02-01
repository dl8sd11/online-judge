#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)

const ll MAXN = 150005;

ll n;
vector<ll> kit[MAXN];
ll par[MAXN],sz[MAXN];

void init() {
    REP1 (i,n) {
        par[i] = i;
        sz[i] = 1;
    }
}
ll fnd(ll x) {
    return par[x] == x ? x : (par[x] = fnd(par[x]));
}

void uni(ll x,ll y) {
    if (sz[x=fnd(x)] < sz[y=fnd(y)]) {
        swap(x,y);
    }
    par[y] = x;
    sz[x] += sz[y];
    for (auto v : kit[y]) {
        kit[x].emplace_back(v);
    }
    kit[y].clear();
    kit[y].shrink_to_fit();
}
/********** Good Luck :) **********/
int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    init();

    REP1 (i,n) {
        kit[i].emplace_back(i);
    }
    REP (i,n-1) {
        ll x,y;
        cin >> x >> y;
        uni(x,y);
    }
    REP1 (i,n) {
        if (kit[i].size()) {
            for (auto v : kit[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
