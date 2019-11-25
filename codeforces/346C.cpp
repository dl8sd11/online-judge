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
const int iNF = 0x3f3f3f3f;

int rng, bit[MAXN];

void upd (int x, int val) {
    for (++x; x<MAXN; x+=-x&x) {
        if (bit[x] > val) {
            bit[x] = val;
        }
    }
}

int qry (int x) {
    int ret = iNF;
    for (++x; x>0; x-=-x&x) {
        if (bit[x] < ret) {
            ret = bit[x];
        }
    }
    return ret;
}
//void updSeg (int pos, int val) {
//    for (seg[pos+=rng]=val; pos>1; pos>>=1) {
//        seg[pos>>1] = min(seg[pos], seg[pos^1]);
//    }
//}
//
//int qryMin (int L, int R) {
//    int ret = iNF;
//    for (L+=rng, R+=rng; L<R; L>>=1, R>>=1) {
//        if (L&1) {
//            ret = min(ret, seg[L++]);
//        }
//        if (R&1) {
//            ret = min(ret, seg[--R]);
//        }
//    }
//    return ret;
//}
vector<int> x, dp, factor;

/*********************GoodLuck***********************/
int main () {
    IOS();
    int n, a, b;

#ifdef tmdd
    n = 100000;
#else
    cin >> n;
#endif
    x.resize(n);

    REP (i, n) {
    #ifdef tmdd
        x[i] = i+1;
    #else
        cin >> x[i];
    #endif
    }
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end())-x.begin());

#ifdef tmdd
    a = 1000000000, b = 1000000000-1000000;
#else
    cin >> a >> b;
#endif
    rng = a - b + 1;
    factor.resize(rng);
    dp.resize(rng);

    int cnt = 0;
    for (auto v : x) {
        if (v == 2) {
            continue;
        }
        for (register int i=(b+v-1)/v*v; i<a; i+=v) {
            factor[i-b] = max(factor[i-b], v);
        }
    }

    memset(bit, iNF, sizeof(bit));
    upd(rng-1, 0);
    for (int i=rng-2; i>=0; i--) {
        dp[i] = min(dp[i+1], qry(min(i+factor[i], rng)-1)) + 1;
        upd(i, dp[i]);
    }

    cout << dp[0] << endl;
}
