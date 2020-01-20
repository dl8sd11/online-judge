#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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

const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k, D[MAXN], tran[7][MAXN];
ll dp[7][MAXN], pre[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP1 (i, n) {
        cin >> D[i];
        pre[i] = pre[i-1] + D[i];
    }

    REP1 (i, n) {
        dp[0][i] = -INF;
    }
    dp[0][0] = 0;

    for (int d=1; d<=k; d++) {
        ll mx = dp[d-1][0];
        int pos = 0;
        dp[d][0] = -INF;
        for (int i=1; i<=n; i++) {
            if (dp[d-1][i-1]+pre[i-1]*(d&1?-1:1) >= mx) {
                mx = dp[d-1][i-1]+pre[i-1]*(d&1?-1:1);
                pos = i-1;
            }
            dp[d][i] = mx + pre[i]*(d&1?1:-1);
            tran[d][i] = pos;
        }
    }

    n = tran[k--][n];
    for (; n>=1; ) {
        cout << n << endl;
        n = tran[k--][n];
    }
    assert(k == 0);

}
