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

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, a[MAXN], f[MAXN];
ll k;

bool solve (ll val) {
    ll sum = 0;
    REP (i, n) {
        ll rem = val / f[i];
        sum += max(0LL, a[i] - rem);
        debug(a[i]-rem);
    }

    return sum <= k;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
    }
    REP (i, n) {
        cin >> f[i];
    }

    sort(a, a+n);
    sort(f, f+n, greater<int>());

    solve(2);

    ll L = -1, R = 1000000000012LL;
    while (L < R - 1) {
        ll M = (L + R) >> 1;
        if (solve(M)) {
            R = M;
        } else {
            L = M;
        }
    }

    cout << R << endl;
}
