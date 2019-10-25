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

const int MAXN = 200005;
const int MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k;
ll seg[MAXN*2];

ll qry (int l, int r) {
    ll ret = INF;
    for (l+=(n+1), r+=(n+1); l<r; l>>=1, r>>=1) {
        if (l&1) {
            ret = min(ret, seg[l++]);
        }
        if (r&1) {
            ret = min(ret, seg[--r]);
        }
    }
    return ret;
}

void chg (int p, ll v) {
    for (seg[p+=(n+1)]=v; p>1; p>>=1) {
        seg[p>>1] = min(seg[p], seg[p^1]);
    }
}
ll dp[MAXN];
bool rt[MAXN];
set<int> rts;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;

    REP1 (i, n) {
        char c;
        cin >> c;
        rt[i] = c == '1';
        if (rt[i]) {
            rts.insert(i);
        }
    }

    chg(0, 0);
    REP1 (i, n) {
        dp[i] = dp[i-1] + i;
        auto ptr = rts.lower_bound(i-k);
        if (ptr != rts.end() && *ptr <= i+k-1) {
            dp[i] = min(dp[i], qry(*ptr-k-1, i) + *ptr);
        }
        chg(i, dp[i]);
        debug(dp[i]);
    }

    cout << dp[n] << endl;
    return 0;
}
