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

const int MAXN = 500005;
const ll MOD = 1000000007;
const double eps = 1e-9;

ll n, k;
ll a[MAXN];

ll test (double edge) {
    ll sum = 0;
    REP (i, n) {
        sum += ceil(sqrt(a[i]/edge)-1);
    }
    return sum;
}

double solve (double edge) {
    double time = 0;
    ll tot = 0;
    REP (i, n) {
        double p = ceil(sqrt(a[i]/edge)-1) + 1;
        time += a[i] / p;
        tot += p;
    }

    return time;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
#ifndef tmd
    freopen("tallbarn.in", "r", stdin);
    freopen("tallbarn.out", "w", stdout);
#endif
    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
    }

    double L = 0, R = 1e13;
    while (L < R - eps) {
        double M = (L + R) / 2;
        if (test(M) > k-n) {
            L = M;
        } else {
            R = M;
        }
    }

    debug(R);
    debug(test(R));

    cout << fixed << setprecision(0) << round(solve(R)) << endl;

}
