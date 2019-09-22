#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll ans = INF;

#define X first
#define Y second

void upd (pll &p, ll x) {
    p.X = min(p.X, x);
    p.Y = max(p.Y, x);
}
void solve (ll w, ll h) {
    REP1 (i, w) {
        pll sz = {INF, -INF};
        upd(sz, i * h);
        {
            pll nw = sz;
            upd(nw, (w-i)/2 * h);
            upd(nw, (w-i+1)/2 * h);
            ans = min(ans, nw.Y- nw.X);
        }
        {
            pll nw = sz;
            upd(nw, h/2 * (w-i));
            upd(nw, (h+1)/2 * (w-i));
            ans = min(ans, nw.Y- nw.X);
        }

    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    ll w, h;
    cin >> w >> h;

    solve(h, w);
    solve(w, h);

    cout << ans << endl;
    return 0;
}
