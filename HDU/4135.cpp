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

const int MAXN = 100006;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

vector<int> dv;

void dfs (int idx, int cnt, int pdt, ll &ans, ll x) {
    if (idx == SZ(dv)) {
        ll cur = x / pdt;
        //debug(cnt, pdt);
        ans += (cnt & 1) ? -cur : cur;
    } else {
        dfs(idx + 1, cnt, pdt, ans, x);
        dfs(idx + 1, cnt + 1, pdt * dv[idx], ans, x);
    }
}

ll solve (int n, ll x) {
    int tmp = n;
    dv.clear();
    for (int i=2; i*i<=tmp; i++) {
        if (tmp % i == 0) {
            while (tmp % i == 0) {
                tmp /= i;
            }
            dv.emplace_back(i);
        }
    }
    if (tmp != 1) {
        dv.emplace_back(tmp);
    }

    ll ret = 0;
    dfs(0, 0, 1, ret, x);

    return ret;
}

ll msolve (int n, int l, int x) {
    ll cnt = 0;
    for (int i=l; i<=x ;i++) {
        cnt += __gcd(n, i) == 1;
    }
    return cnt;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    ll t, n, l, r;
    cin >> t;
    while (t--) {
        cin >> n >> l >> r;
        cout << solve(n, r) - solve(n, l-1) << endl;
        #ifdef tmd
            ll ret = solve(n, r) - solve(n, l-1);
            debug(ret, msolve(n, l, r));
        #endif
    }

    return 0;
}
