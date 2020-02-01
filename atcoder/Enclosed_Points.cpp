#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
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
const ll MOD = 998244353;


ll n;
pii pt[MAXN];
vector<ll> xval, yval;
ll ans;

ll mpow (ll ep, ll bs) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

ll bit[MAXN];

void add (ll x) {
    for (x++; x<MAXN; x+=-x&x) {
        bit[x]++;
    }
}

ll qry (ll x) {
    ll ret = 0;
    for (x++; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> pt[i].first >> pt[i].second;
        xval.emplace_back(pt[i].first);
        yval.emplace_back(pt[i].second);
    }

    {
        sort(xval.begin(), xval.end());
        sort(yval.begin(), yval.end());
        xval.resize(unique(xval.begin(), xval.end())-xval.begin());
        yval.resize(unique(yval.begin(), yval.end())-yval.begin());
    }

    REP (i, n) {
        pt[i].first = lower_bound(xval.begin(),xval.end(), pt[i].first)-xval.begin();
        pt[i].second = lower_bound(yval.begin(),yval.end(), pt[i].second)-yval.begin();
    }

    sort(pt, pt+n);

    ll total = mpow(n, 2);
    REP (i, n) {
    debug(i);
        int l = pt[i].first;
        int r = n - pt[i].first - 1;
        int u = n - pt[i].second - 1;
        int d = pt[i].second;

        int ld = qry(pt[i].second);
        int lu = l -ld;
        int rd = d - ld;
        int ru = r - rd;
        debug(l, u, r, d, lu, ld, ru, rd);
        assert(l >= 0);
        assert(r >= 0);
        assert(u >= 0);
        assert(d >= 0);
        assert(lu >= 0);
        assert(ld >= 0);
        assert(ru >= 0);
        assert(rd >= 0);

        ll cur = 0;
        cur -= (1 + mpow(l, 2) + mpow(r, 2) + mpow(u, 2) + mpow(d, 2));
        cur %= MOD;
        cur += (total + mpow(ld, 2) + mpow(lu, 2) + mpow(ru, 2) + mpow(rd, 2));
        cur %= MOD;
        if (cur < 0) {
            cur += MOD;
        }

        add(pt[i].second);

        ans = (ans + cur) % MOD;
    }

    cout << ans << endl;
}
