#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 51;
const ll MOD = 998244353;

int n, l[MAXN], r[MAXN];
ll dp[MAXN][MAXN*2];

vector<int> v;

ll mpow (ll bs, ll ep) {
    ll res = 1;
    while (ep) {
        if (ep & 1) {
            res = res * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return res;
}

ll cob (ll r, ll k) {
    ll res = 1;
    REP1 (i, k) {
        res = res * (r-i+1) % MOD;
        res = res * mpow(i, MOD-2) % MOD;
    }
    return res;
}

ll h (ll r, ll k) {
    return cob(r+k, k);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    v = {-1,998244352};


    ll tot = 1;
    REP1 (i, n) {
        cin >> l[i] >> r[i];
        v.eb(l[i]);
        v.eb(r[i] + 1);
        tot = tot * (r[i]-l[i]+1) % MOD;
    }
    debug(tot);
    debug(mpow(tot, MOD-2));

    sort(ALL(v));
    v.resize(unique(ALL(v))-v.begin());

    debug(v);
    REP (j, SZ(v)) {
        dp[0][j] = 1;
    }

    for (int i=1; i<=n; i++) {
        for (int j=1; j<SZ(v)-1; j++) {
            dp[i][j] = dp[i][j-1];
            for (int k=i; k>=1; k--) {
                if (l[k]<=v[j] && v[j+1]-1<=r[k]) {
                    dp[i][j] += dp[k-1][j-1] * h(v[j+1]-v[j]-1,i-k+1);
                    dp[i][j] %= MOD;
                } else {
                    break;
                }
            }
        }
    }

    ll ans = dp[n][SZ(v)-2];
    debug(ans*mpow(tot, MOD-2)%MOD);

    REP1 (i, n) {
        ans = ans * mpow(r[i]-l[i]+1, MOD-2) % MOD;
    }

    cout << ans << endl;

#ifdef tmd

    int x, y;
    while (cin >> x >> y) {
        debug(dp[x][y]);
    }

#endif // tmd
}
