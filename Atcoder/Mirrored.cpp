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

const int MAXN = 1000006;
const ll MOD = 1000000007;
ll ans = 0, pw[21];
void dfs (ll id, ll len, ll d, ll x = 1) {
    if (id == len/2) {
        if (d == 0) {
            ans += x * ((len & 1) ? 10 : 1);
        }
    } else {
        ll lb = -10, ub = 10;
        ll rt = pw[len-id-1] - pw[id];
        for (ll i=-9; i<=9; i++) {
            if (rt * i <= d) {
                lb = max(lb, i);
            } else {
                ub = min(ub, i);
            }
        }
        if (lb > -10) {
            dfs(id+1, len, d-lb*rt, x * (10 - abs(lb) - (!id)));
        }
        if (ub < 10) {
            dfs(id+1, len, d-ub*rt, x * (10 - abs(ub) - (!id)));
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    pw[0] = 1;
    REP1 (i, 18) {
        pw[i] = pw[i-1] * 10;
    }

    ll d;
    cin >> d;

    REP1 (i, 18) {
        dfs(0, i, d);
    }

    cout << ans << endl;
    return 0;
}
