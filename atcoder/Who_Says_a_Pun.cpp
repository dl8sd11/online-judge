#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define X first
#define Y second
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

const int MAXN = 5003;
const ll MOD = 1000000007;

ll mpow (ll bs, ll ep, ll md) {
    ep %= (md - 1);
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % md;
        }
        ep >>= 1;
        bs = bs * bs % md;
    }
    return ret;
}

struct Hash {
    int n;
    string s;

    pii pre[MAXN], inv[MAXN];
    pii a;
    const pii MOD = {1000000009, 1000000007};
    Hash (string &str) : n(SZ(str)), s(str) {
        a.X = rand() % 300 + 300;
        a.Y = rand() % 300 + 300;
        inv[0] = {1, 1};

        REP1 (i, n) {
            inv[i].X = mpow(a.X, i * (MOD.X - 2LL), MOD.X);
            inv[i].Y = mpow(a.Y, i * (MOD.Y - 2LL), MOD.Y);
        }

        pll bs = {1, 1};
        REP1 (i, n) {
            pre[i].X = (pre[i-1].X + s[i-1] * bs.X) % MOD.X;
            pre[i].Y = (pre[i-1].Y + s[i-1] * bs.Y) % MOD.Y;
            bs.X = bs.X * a.X % MOD.X;
            bs.Y = bs.Y * a.Y % MOD.Y;
        }
    }

    pii get (int l, int r) {
        pll dl;
        dl.X = pre[r+1].X - pre[l].X;
        dl.Y = pre[r+1].Y - pre[l].Y;
        if (dl.X < 0) {
            dl.X += MOD.X;
        }
        if (dl.Y < 0) {
            dl.Y += MOD.Y;
        }

        dl.X = dl.X * inv[l].X % MOD.X;
        dl.Y = dl.Y * inv[l].Y % MOD.Y;
        return dl;
    }
};

/*********************GoodLuck***********************/
int main () {
    IOS();
    srand(2002);

    int n;
    string s;

    cin >> n >> s;
    Hash hasher(s);

    for (int i=n/2; i>=0; i--) {
        set<pii> tbl;

        REP (j, n) {
            if (j >= i*2-1) {
                tbl.insert(hasher.get(j-i*2+1, j-i));
                pii res = hasher.get(j-i*2+1, j-i);
                debug(res.X, res.Y);
            }
            if (j >= i-1) {
                pii res = hasher.get(j-i+1, j);
                debug(res.X, res.Y);
                if (tbl.count(hasher.get(j-i+1, j))) {
                    cout << i << endl;
                    return 0;
                }
            }
        }
    }

    cout << 0 << endl;
    return 0;
}
