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
const ll INF = 0x3f3f3f3f3f3f3f3f;

/*
dp[i] = min{dp[j] + x[i]*(i-j)-(pre[i]-pre[j])}
dp[i] = min{dp[j] + x[i]*i-x[i]*j-pre[i]+pre[j]}
dp[i] = x[i]*i-pre[i]+min{-x[i]*j+pre[j] + dp[j]}
*/

struct Point {
    ll x, y;
};

Point operator- (const Point &p1, const Point &p2) {
    return {p1.x-p2.x, p1.y-p2.y};
}

ll f (const Point &p, ll x) {
    return x*p.x + p.y;
}

typedef long double ld;
ld cross (const Point &p1, const Point &p2) {
    return ld(p1.x)*p2.y-ld(p1.y)*p2.x;
}

Point hull[MAXN];
int hd, tl;

void add_line (ll k, ll b) {
    Point nw = {k, b};
    while (tl-hd>=2 && cross(nw-hull[tl-1], hull[tl-2]-hull[tl-1]) <= 0) {
        tl--;
    }
    hull[tl++] = nw;
}

ll get (ll x) {
    while (tl-hd>=2 && f(hull[hd], x) >= f(hull[hd+1], x)) {
        hd++;
    }
    return f(hull[hd], x);
}

int n, m, p;
ll xpre[MAXN], dp[2][MAXN], d[MAXN], dpre[MAXN], x[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> p;
    for (int i=2; i<=n; i++) {
        cin >> d[i];
        dpre[i] = dpre[i-1] + d[i];
    }

    REP1 (i, m) {
        int h, t;
        cin >> h >> t;
        x[i] = t - dpre[h];
    }
    sort(x+1, x+m+1);

// if every cat is waiting before t = 0
    bool flag = false;// true;
    REP1 (i, m) {
        xpre[i] = x[i] + xpre[i-1];
        if (x[i] >= 0) {
            flag = false;
        }
        debug(x[i]);
    }
    if (flag) {
        ll ans = 0;
        REP1 (i, m) {
            ans += -x[i];
        }
        cout << ans << endl;
        return 0;
    }


// dp[i] = x[i]*i-pre[i]+min{-x[i]*j+pre[j] + dp[j]}

    ll ans = INF;
    REP1 (i, m) {
        dp[0][i] = INF;
    }
    dp[0][0] = 0;

    REP1 (feed, p) {
        bool c = feed&1;
        bool l = c^1;
        hd = tl = 0;
        REP1 (i, m) {
            add_line(i-1, xpre[i-1]+dp[l][i-1]);

            //dp[c][i] = INF;
            //if (x[i] >= 0) {
                dp[c][i] = x[i]*i-xpre[i]+get(-x[i]);
            //}

            if (i == m) {
                ans = min(ans, dp[c][m]);
            }

        }
    }

    cout << ans << endl;
    return 0;
}
