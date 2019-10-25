#include <bits/stdc++.h>
#pragma optimize("Ofast")
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmdd
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

struct Rect {
    ll x, y, a;
};
vector<Rect> rect;

int n;
ll dp[MAXN];

struct point {
    ll x, y;
};

inline point operator- (point &a, point &b) {
    return {a.x-b.x, a.y-b.y};
}

inline ll dot (point &a, point &b) {
    return a.x*b.x+a.y*b.y;
}
typedef long double ld;
const ld cross(const point &a, const point &b) {
    return ld(a.x)*b.y-ld(a.y)*b.x;
}
point hull[MAXN];
int hd = 0, tl = 0;

void add_line (ll k, ll b) {
    point nw = {k, b};
    while (tl-hd>=2 && cross(nw-hull[tl-1], hull[tl-2]-hull[tl-1]) <= 0) {
        tl--;
    }
    hull[tl++] = nw;
}

ll get (ll x) {
    point qry = {x, 1};
    while (tl-hd>=2 && dot(qry,hull[hd]) <= dot(qry, hull[hd+1])) {
        hd++;
    }
    return dot(qry, hull[hd]);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    rect.resize(n);
    REP (i, n) {
        cin >> rect[i].x >> rect[i].y >> rect[i].a;
    }
    sort(rect.begin(), rect.end(), [&](Rect a, Rect b) {
        return a.x < b.x;
    });

    ll ans = 0;
    REP (i, n) {
        ll cur = rect[i].x * rect[i].y - rect[i].a;
        dp[i] = max(0LL, (i ? get(rect[i].y) : 0)) + cur;
        ans = max(dp[i], ans);
        add_line(-rect[i].x, dp[i]);
#ifdef tmdd
        debug(cur, dp[i]);
        for (auto v : hull) {
           // debug(v);
        }
#endif
    }

    cout << ans << endl;
    return 0;
}
