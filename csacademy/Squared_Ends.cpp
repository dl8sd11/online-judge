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


typedef complex<ll> point;
inline ll dot (const point &a, const point &b) {
    return (conj(a)*b).real();
}

inline ll f (const point &a, ll x) {
    return dot(a, {x, 1});
}

point line[4 * MAXN];

void add_line(point nw, int v = 1, int l = 0, int r = MAXN) {
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[v], l);
    bool mid = f(nw, m) < f(line[v], m);
    if(mid) {
        swap(line[v], nw);
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * v, l, m);
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}

ll get(int x, int v = 1, int l = 0, int r = MAXN) {
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(line[v], x);
    } else if(x < m) {
        return min(f(line[v], x), get(x, 2 * v, l, m));
    } else {
        return min(f(line[v], x), get(x, 2 * v + 1, m, r));
    }
}
ll dp[102][10004], a[MAXN];
const ll INF = 0x3f3f3f3f3f3f3f3f;
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n, k;
    cin >> n >> k;
    REP1 (i, n) {
        cin >> a[i];
    }

// dp[i] = a[i]^2 + min(-2a[i]a[j]+a[j]^2+dp[j])
    memset(dp, INF, sizeof(dp));
    dp[0][0] = 0;

    REP1 (p, k) {
        REP (j, MAXN*4) {
            line[j] = {0, INF};
        }
        REP1 (i, n) {
            add_line({-2*a[i],a[i]*a[i]+dp[p-1][i-1]});
            dp[p][i] = a[i]*a[i]+get(a[i]);
            debug(p, i, dp[p][i], a[i]);
        }
    }

    cout << dp[k][n] << endl;
    return 0;

}
