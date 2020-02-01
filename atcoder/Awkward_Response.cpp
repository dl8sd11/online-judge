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
#define debug(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll ans = 1000;

ll cnt;
bool qry (ll x) {
    cnt++;
    assert(cnt <= 64);
    assert(x >= 1 && x <= 1000000000000000000LL);
    cout << "? " << x << endl;
    #ifdef tmd
    string sa = to_string(ans);
    string sx = to_string(x);
    return (x <= ans && sx <= sa) || (x > ans && sx > sa);
    #else
    char res;
    cin >> res;
    return res == 'Y';
    #endif
}
/*********************GoodLuck***********************/
int main () {
    IOS();

#ifdef tmd
    cin >> ans;
#endif // tmd

    ll bs = 1;
    ll dg = 0;

    ll tt = INF;
    ll ft = -1;
    REP (i, 12) {
        bs *= 10;
        bool q1 = qry(bs), q2 = qry(bs-1);
        debug(q1, q2);
        if (!q1 && q2) {
            dg = i;
            ft = bs;
            break;
        } else if (q1 && q2) {
            tt = min(tt, bs);
        }
    }

    debug(tt, ft);

    if (tt < INF && ft == -1) {
        cout << "! " << tt / 10 << endl;
        return 0;
    } else if (tt == ft / 10) {
        cout << "! " << ft - 1 << endl;
        return 0;
    }
    ll cur = 0;
    REP (i, dg) {
        ll l = 0, r = 10;
        while (l < r - 1) {
            ll m = (l + r) >> 1;
            if (qry(cur * 10 + m)) {
                l = m;
            } else {
                r = m;
            }
        }
        cur = cur * 10 + l;
    }

    ll l = -1, r = 10;
    while (l < r - 1) {
        ll m = (l + r) >> 1;
        if (qry(cur * 100 + m*10 + 9)) {
            r = m;
        } else {
            l = m;
        }
    }
    cur = cur * 10 + r;


    debug(cur);

    cout << "! " << cur << endl;
    return 0;
}
