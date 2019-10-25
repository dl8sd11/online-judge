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
const ll MOD = 1000000007;

string s;
int lst[26], nxt[MAXN][26], dp[MAXN], fwd[MAXN][26];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> s;
    int n = SZ(s);
    REP1 (i, n+1) {
        REP (j, 26) {
            nxt[i][j] = lst[j];
        }
        if (i != n+1) {
            lst[s[i-1]-'a'] = i;
        }
    }

    fill(lst, lst+26, n+1);
    for (int i=n; i>=0; i--) {
        REP (j, 26) {
            fwd[i][j] = lst[j];
        }
        if (i) {
            lst[s[i-1]-'a'] = i;
        }
    }

    dp[0] = n + 1;
    int len = 0;
    REP1 (i, MAXN-1) {
        int mn = n + 1;
        REP (j, 26) {
            mn = min(mn, nxt[dp[i-1]][j]);
        }
        dp[i] = mn;
        len = i;
        debug(i, dp[i]);
        if (dp[i] == 0) {
            break;
        }
    }

    debug(len);
    string ans;
    int cur = 0;
    REP (i, len) {
        REP (j, 26) {
            if (dp[len-i-1] <= fwd[cur][j]) {
                ans += 'a' + j;
                cur = fwd[cur][j];
                break;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
