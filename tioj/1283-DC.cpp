#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

int n, m;
ll cx, cy;
ll up[MAXN][2], lw[MAXN][2];
ll dp[MAXN];

ll trans (int uid, int lid) {
    return max(0LL, lw[lid][1] - up[uid][1]) * max(0LL, up[uid][0] - lw[lid][0]);
}

void solve (int nL, int nR, int mL, int mR) {
    if (nL < nR) {
        int nM = (nL + nR) >> 1;
        debug(nL, nM, nR);
        int tr = mL;

        for (int i=mL; i<mR; i++) {
            ll cur = trans(nM, i);
            if (cur > dp[nM]) {
                dp[nM] = cur;
                tr = i;
            }
        }

        solve(nL, nM, mL, tr+1);
        solve(nM+1, nR, tr, mR);
    }
}

inline int redi() {
    int ret = 0,f = 0;char ch = getchar_unlocked();
    while (isdigit (ch)) {
        ret = ret*10  + ch - 48;
        ch = getchar_unlocked();
    }
    return f?-ret:ret;
}

inline void print(ll x) {
    ll y=10;
    int len=1;
    while(y<=x)    {y*=10;len++;}
    while(len--){y/=10;putchar_unlocked(x/y+48);x%=y;}
}

/*********************GoodLuck***********************/
int main () {

    n = redi();
    REP (i, n) {
        int d = redi();
        if (i&1) {
            cy += d;
        } else {
            cx += d;
            up[i>>1][0] = cx;
            up[i>>1][1] = cy;
        }
    }

    m = redi();
    cx = cy = 0;
    REP (i, m) {
        int d = redi();
        if (i&1) {
            cx += d;
        } else {
            cy += d;
            lw[i>>1][0] = cx;
            lw[i>>1][1] = cy;
        }
    }

    solve(0, n/2, 0, m/2);

    ll ans = 0;
    REP (i, n) {
        ans = max(ans, dp[i]);
    }

    print(ans);
    return 0;
}

