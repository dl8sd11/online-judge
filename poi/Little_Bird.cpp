//#pragma GCC optimize("O3","unroll-loops")
//#pragma GCC target("avx","avx2","fma")
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

const int MAXN = 1000005;
const int MOD = 1000000007;

int n, d[MAXN], q, id[MAXN], dp[MAXN];

struct SegmentTree {
    int dt[MAXN<<1];
   // vector<int> dt;

    SegmentTree () {
        memset(dt, 0x3f, sizeof(dt));
    }

    void chg (int x, int v) {
        for (dt[x+=n]=v; x>1; x>>=1) {
            dt[x>>1] = min(dt[x], dt[x^1]);
        }
    }

    int qry (int l, int r) {
        int res = MOD;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) {
                res = min(res, dt[l++]);
            }
            if (r&1) {
                res = min(res, dt[--r]);
            }
        }
        return res;
    }
};

SegmentTree rmq;
/*********************GoodLuck***********************/

int main () {
    IOS();

    #ifdef tmdd
    n = 1000000;
    #else
    cin >> n;
    #endif // tmd

    vector<pii> hei;
    hei.reserve(n);

    REP1 (i, n) {
        #ifdef tmdd
        d[i] = i % 1000 == 0 ? 2 : 1;
        #else
        cin >> d[i];
        #endif // tmd
        hei.eb(d[i], i);
    }
    sort(ALL(hei));

    REP (i, n) {
        id[hei[i].Y] = i;
    }

    #ifdef tmdd
    q = 25;
    #else
    cin >> q;
    #endif // tmd
    REP1 (_u_, q) {
        int k;
        #ifdef tmdd
        k = _u_;
        #else
        cin >> k;
        #endif // tmd


//        pary(id+1,id+n+1);
        dp[1] = 0;
        rmq.chg(id[1], 0);

        for (int i=2; i<=n; i++) {
            int pos = lower_bound(ALL(hei), pii(d[i], MOD))-hei.begin();
            dp[i] = min(rmq.qry(0,pos)+1, rmq.qry(pos, n));
         //   continue;
            rmq.chg(id[i], dp[i]);

            if (i-k >= 1) {
                rmq.chg(id[i-k], MOD);
            }

        }
        for (int i=max(0, n-k+1); i<=n; i++) {
            rmq.chg(id[i], MOD);
        }
        pary(dp+1, dp+n+1);

        cout << dp[n] << '\n';
    }
}
