#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define ckMin(i, n) i=min(i,(__typeof__(i))(n))
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

const int MAXN = 100005;
const ll MOD = 1000000007;

pair<int,int> pos[MAXN];
int dp[MAXN], n, m;

int fitRange (int &x) {
    x = min(m, max(1, x));
    return x;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m;
    REP (i, n) {
        cin >> pos[i].first >> pos[i].second;
        pos[i] = {pos[i].first-pos[i].second, pos[i].first+pos[i].second};
        fitRange(pos[i].first);
        fitRange(pos[i].second);
    }

    dp[0] = 0;
    for (int i=1; i<=m; i++) {
        dp[i] = dp[i-1] + 1;
        REP (j, n) {
            if (pos[j].first <= i && i <= pos[j].second) {
                ckMin(dp[i], dp[pos[j].first-1]);
            } else if (pos[j].second <= i) {
                int len = i - pos[j].second;
                ckMin(dp[i], dp[max(0, pos[j].first-len-1)]+len);
            }
        }
    }

    cout << dp[m] << endl;
}
