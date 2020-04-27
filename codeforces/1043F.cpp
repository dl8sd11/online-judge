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

const int MAXN = 300005;
const ll MOD = 1190494771;

ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep&1) {
            ret = ret * bs % MOD;
        }
        ep >>= 1;
        bs = bs * bs % MOD;
    }
    return ret;
}

int fac[MAXN], inv[MAXN];

void build () {
    fac[0] = inv[0] = 1;
    for (int i=1; i<MAXN; i++) {
        fac[i] = 1LL * fac[i-1] * i % MOD;
        inv[i] = mpow(fac[i], MOD-2);
    }
}

int n, a[MAXN], mcnt[MAXN];

void sub (int &x, int val) {
    x = x - val < 0 ? x - val + MOD : x - val;
}

int cob (int x, int y) {
    if (x < y) return 0;
    return 1LL * fac[x] * inv[y] % MOD * inv[x-y] % MOD;
}

bool solve (int sz) {
    vector<int> dp(MAXN, 0);

    for (int i=MAXN-1; i>=1; i--) {
        dp[i] = cob(mcnt[i], sz);
        for (int j=2; j*i<MAXN; j++) {
            sub(dp[i], dp[i*j]);
        }
    }

    pary(dp.begin(), dp.begin() + 20);
    return dp[1] != 0;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    build();
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
        mcnt[a[i]]++;
    }

    for (int i=1; i<MAXN; i++) {
        for (int j=i*2; j<MAXN; j+=i) {
            mcnt[i] += mcnt[j];
        }
    }
    pary(mcnt, mcnt+20);

    for (int i=1; i<=8; i++) {
        if (solve(i)) {
            cout << i << endl;
            return 0;
        }
    }

    cout << -1 << endl;
}

