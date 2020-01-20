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


const int MAXT = 20004;
const int MAXN = 51;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

/*
Solution:

1.
dp[k][t] = min(dp[k-1][i] + cost[i+1][t])
Divide and Conquer O(K*NlgN*C) C for calculate cost

pre-calculate
vector<ll> mask[i]; every mask change with left border i
int cnt[B][2^B][20000]; prefix sum with mask 2^B in group B

=> fail because the function is not convex

2.
dp[k][t] = min(dp[k-1][i] + cost[i+1][t])
for every dp[k][t] ac contestant only change N times

maintain the n+1 segment with their optimal point for every t

for t + 1 there may be some changes for the segment with the following form:
- merge two segment
- add new segment

after that for every dp[k][t] we can use O(n) time calculate their min cost
*/

int n, t, s, pts[MAXT];
bool ac[MAXN][MAXT];
int dp[MAXN][MAXT];

int calCost (int l, int r) {
    int res = 0;
    REP (i, n) {
        int cur = 0;
        for (int j=l;j<=r;j++) {
            cur += pts[j];
            if (!ac[i][j]) {
                cur = 0;
                break;
            }
        }
        res += cur;
    }
    return res;
}

void tran (int k, int l, int r) {
    if (l < r) {
        int cost = calCost(l+1,r);
        if (dp[k-1][l]+cost < dp[k][r]) {
            dp[k][r] = dp[k-1][l] + cost;
        }
    }
}

void solve (int k) {

}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> t >> s;
    REP1 (i, t) {
        cin >> pts[i];
    }
    REP (i, n) {
        REP1 (j, t) {
            char c;
            cin >> c;
            ac[i][j] = c == '1';
        }
    }
    debug(calCost(1,2));

    memset(dp, 0x3f3f3f3f, sizeof(dp));
    dp[0][0] = 0;
    REP1 (i, s) {
        solve(i);
        cout << dp[i][t] << endl;
    }



}
