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
tree<int,null_type,greater<int>,rb_tree_tag,tree_order_statistics_node_update> sub[MAXN];

void mrg (int i, int j) {
    if (SZ(sub[i]) < SZ(sub[j])) {
        swap(sub[i], sub[j]);
    }
    for (auto v : sub[j]) {
        sub[i].insert(v);
    }
}

void dfs (int nd) {
    for (auto v : edge[nd]) {
        dfs(v);
        mrg(nd, v);
    }
    ans[nd] = sub[nd].order_of_key(p[nd]);
    sub[nd].insert(p[nd]);
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
    REP1 (i, n) {
        cout << ans[i] << endl;
    }
}
