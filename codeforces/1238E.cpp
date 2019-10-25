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

const int MAXN = 21;
const ll MOD = 1000000007;

int n, m;
int adj[MAXN][MAXN], dp[1<<MAXN];
vector<int> msk[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m;
    int lst = m;
    REP (i, n) {
        char c;
        cin >> c;
        if (lst != c-'a') {
            adj[c-'a'][lst]++;
            adj[lst][c-'a']++;
        }
        lst = c-'a';
    }

    REP (i, (1<<m)) {
        int cnt = 0;
        REP (j, m) {
            cnt += (i>>j) & 1;
        }
        msk[cnt].emplace_back(i);
    }

    memset(dp, 0x3f3f3f3f3f3f3f3f, sizeof(dp));
    dp[0] = 0;
    REP1 (i, m) {
        for (auto sk : msk[i]) {
            debug(i, sk);
            for (int j=0; j<m; j++) {
                if (sk & (1<<j)) {
                    int cur = dp[sk^(1<<j)];
                    for (int k=0; k<m; k++) {
                        if (sk & (1<<k)) {
                            cur += adj[j][k] * i;
                        } else {
                            cur -= adj[j][k] * i;
                        }
                    }
                    dp[sk] = min(dp[sk], cur);
                }
            }
            debug(dp[sk]);
        }
    }

    cout << dp[(1<<m)-1] << endl;
}
