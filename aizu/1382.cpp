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

const int MAXN = 500005;
const ll INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<int, int> pii;

int n, k, dp[MAXN];
char s[MAXN], t[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    s[0] = t[0] = 'X';
    REP1 (i, n) {
        cin >> s[i];
    }
    REP1 (i, n) {
        cin >> t[i];
    }

    dp[0] = 0;
    int df = 0, ft = 0;
    vector<pii> que;
    REP1 (i, n) {
        if (t[i] != t[i-1]) {
            df++;
        }
        int cur = (-df + 1 + 2) + dp[i-1] * 2;
        while (SZ(que) > ft && cur <= que.back().second) {
            que.pop_back();
        }
        que.emplace_back(i, cur);

        debug(i, df);
        for (int j=ft; j<SZ(que); j++) {
            debug(que[j].first, que[j].second);
        }
        if (s[i] == t[i]) {
            dp[i] = dp[i-1];
        } else {
            while (i - que[ft].first + 1 > k) {
                ft++;
            }
            dp[i] = (que[ft].second + df) / 2;
        }

        debug(dp[i]);
    }

    cout << dp[n] << endl;
    return 0;
}
