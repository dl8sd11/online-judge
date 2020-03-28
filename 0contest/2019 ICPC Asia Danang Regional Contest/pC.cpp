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

const int MAXN = 100005;
const ll MOD = 1000000007;

ll n;
int p, k;
ll ten[MAXN];

typedef array<int,10> ar;

ar mrg (const ar &a1, const ar &a2) {
    ar ret = {};
    REP (i, p) {
        REP (j, p) {
            int nxt = i + j >= p ? i+j-p : i+j;
            ret[nxt] += 1LL * a1[i] * a2[j] % MOD;
            if (ret[nxt] >= MOD) {
                ret[nxt] -= MOD;
            }
        }
    }
    return ret;
}

void upd (ar &dp, int cof) {
    ar res = {};
    for (int i=0; i<p; i++) {
        for (int d=0; d<10; d++) {
            int nxt = (i + d * cof) % p;
            res[nxt] += dp[i];
            res[nxt] %= MOD;
        }
    }

    dp = res;
}
void upd2 (ar &dp, int cof) {
    ar res = {};
    for (int i=0; i<p; i++) {
        for (int d=1; d<10; d++) {
            int nxt = (i + d * cof) % p;
            res[nxt] += dp[i];
            res[nxt] %= MOD;
        }
    }

    dp = res;
}

ar mpow (ar bs, ll ep) {
    ar ret = {};
    ret[0] = 1;
    while (ep) {
        if (ep & 1) {
            ret = mrg(ret, bs);
        }
        bs = mrg(bs, bs);
        ep >>= 1;
    }
    return ret;
}

void valid (ar ans) {
    ar base = {};
    if (n & 1) {
        REP (i, 10) {
            base[ten[(n/2)%(p-1)]*i%p] += 1;
        }
    } else {
        base[0] = 1;
    }

    for (int i=0; i<n/2; i++) {
        if (i) {
            upd(base, (ten[i%(p-1)]+ten[(n-i-1)%(p-1)])%p);
        } else {
            upd2(base, (ten[i%(p-1)]+ten[(n-i-1)%(p-1)])%p);
        }
    }

    pary(base.begin(), base.end());
    pary(ans.begin(), ans.end());
    assert(base == ans);
}

/*********************GoodLuck***********************/
int main () {
    IOS();


    ten[0] = 1;

    int x = 0;
    int sz = 0;
    REP1 (i, p) {
        ten[i] = ten[i-1] * 10 % p;
        if (ten[i] == 1 && sz == 0) {
            sz = i;
        }
    }

    cin >> n >> p >> k;
    ar base = {}, mid = {};
    if (n & 1) {
        REP (i, 10) {
            mid[ten[(n/2)%(p-1)]*i%p] += 1;
        }
    } else {
        mid[0] = 1;
    }

    base[0] = 1;
    REP1 (i, p-1) {
        upd(base, (ten[i] + ten[(n-i-1) % (p-1)]) % p);
    }

    ll n2 = (n-2)/2;
    pary(base.begin(), base.end());
    base = mpow(base, n2/(p-1));
    pary(base.begin(), base.end());

    for (ll i=n2/(p-1)*(p-1)+1; i<n/2; i++) {
        debug(i);
        upd(base, (ten[i%(p-1)]+ten[(n-i-1)%(p-1)])%p);
    }

    base = mrg(base, mid);
    upd2(base, (ten[0]+ten[n-1])%p);

    #ifdef tmd

    valid(base);

    #endif // tmd

    assert(base[k] < MOD);
    cout << base[k] << endl;
}
