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

const int MAXN = 10000006;
const ll MOD = 1000000007;

string s, t;

int z[MAXN], bst, dp[MAXN];
int cnts;

inline char sat (int pos) {
    if (pos < SZ(t)) {
        return t[pos];
    } else if (pos == SZ(t)) {
        return '@';
    } else {
        return s[(pos-SZ(t)-1)%SZ(s)];
    }
}
int calc (int ss) {
    memset(z, 0, sizeof(z));
    memset(dp, 0, sizeof(dp));
    bst = 0;

    int sz = SZ(t) + 1 + ss * SZ(s);
    assert(sz < MAXN);
    debug(sz);

    REP1 (i, sz-1) {
        if (bst+z[bst] > i) {
            z[i] = min(bst+z[bst]-i, z[i-bst]);
        }

        while (i+z[i] < sz && sat(z[i]) == sat(i+z[i])) {
            z[i]++;
        }
        if (i+z[i] >= bst+z[bst]) {
            bst = i;
        }
    }

    int ret = 0;
    for (int i=SZ(t)+1; i<sz; i++) {
        if (z[i] == SZ(t)) {
            dp[i] = dp[i-SZ(t)] + 1;
            ret = max(ret, dp[i]);
        }
    }

    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> s >> t;

    cnts = (SZ(t)+SZ(s)-1)/SZ(s);

    int ans1 = calc(5*cnts);

    int ans2 = calc(7*cnts);

    if (ans2 > ans1) {
        cout << -1 << endl;
    } else {
        cout << ans1 << endl;
    }
    return 0;
}
