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

ll pre(ll x) {
    ll b = 1;
    ll ret = 0;
    ll cnt = 1;
    while (b*10-1 <= x) {
        ll l = b, r = b*10-1;
        ll sum = (x-l+1+x-r+1) * (r-l+1) / 2;
        ret += sum * (cnt++);
        b *= 10;
    }

    ll cur = (1 + x-b+1) * (x-b+1) / 2;
    ret += cur * cnt;
    return ret;
}
ll f(ll x) {
    ll b = 1;
    ll ret = 0;
    ll cnt = 1;
    while (b*10-1 <= x) {
        ll l = b, r = b*10-1;
        ret += (r-l+1) * (cnt++);
        b *= 10;
    }
    ret += (x-b+1) * cnt;
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int q;
    cin >> q;
    while (q--) {
        ll d;
        cin >> d;

        ll L = 0, R = 1000000001;
        while (L < R - 1) {
            ll M = (L + R) >> 1;
            if (pre(M) < d) {
                L = M;
            } else {
                R = M;
            }
        }

        d -= pre(L);
        R = L + 2;
        L = 0;
        while (L < R - 1) {
            ll M = (L + R) >> 1;
            if (f(M) < d) {
                L = M;
            } else {
                R = M;
            }
        }

        string nxt = to_string(R);
        cout << nxt[d-f(L)-1] << endl;
    }
    return 0;
}
