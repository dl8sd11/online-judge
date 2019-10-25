#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) ll(i.size())
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

int n, m, q;
ll ans, deg[MAXN];
vector<int> in[MAXN];

void upd (int nd, int add) {
    ans -= (deg[nd] - SZ(in[nd])) * SZ(in[nd]);
    in[nd].emplace_back(add);
    ans += (deg[nd] - SZ(in[nd])) * SZ(in[nd]);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int f, t;
        cin >> f >> t;
        if (f < t) {
            swap(f, t);
        }
        deg[f]++;
        deg[t]++;
        in[t].emplace_back(f);
    }
    REP1 (i, n) {
        ans += (deg[i] - SZ(in[i])) * SZ(in[i]);
    }

    cin >> q;
    cout << ans << endl;
    while (q--) {
        int d;
        cin >> d;
        ans -= (deg[d] - SZ(in[d])) * SZ(in[d]);
        for (auto v : in[d]) {
            upd(v, d);
        }

        cout << ans << endl;
        in[d].clear();
    }
    return 0;
}
