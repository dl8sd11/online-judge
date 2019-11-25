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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

int n, p[MAXN], ans[MAXN];
vector<int> edge[MAXN];

int bit[MAXN];
void add (int x) {
    for (x++; x<MAXN; x+=-x&x) {
        bit[x]++;
    }
}

int qry (int x) {
    int ret = 0;
    for (x++; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int in[MAXN], out[MAXN], tme;
void dfs (int nd) {
    in[nd] = tme++;
    for (auto v : edge[nd]) {
        dfs(v);
    }
    out[nd] = tme;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
#ifndef tmd
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
#endif

    cin >> n;
    REP1 (i, n) {
        cin >> p[i];
    }
    for (int i=2; i<=n; i++) {
        int f;
        cin >> f;
        edge[f].emplace_back(i);
    }

    dfs(1);

    vector<int> id;
    REP1 (i, n) {
        id.emplace_back(i);
    }
    sort(id.begin(), id.end(), [&](int p1, int p2) {
        return p[p1] > p[p2];
    });

    for (auto v : id) {
        debug(in[v], out[v], v);
        ans[v] = qry(out[v]-1)-qry(in[v]);
        add(in[v]);
    }

    REP1 (i, n) {
        cout << ans[i] << endl;
    }
}
