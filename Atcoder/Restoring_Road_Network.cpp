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

const int MAXN = 302;
const ll MOD = 1000000007;

int dis[MAXN][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n;
    cin >> n;
    REP (i, n) {
        REP (j, n) {
            cin >> dis[i][j];
        }
    }

    bool no_ans = false;
    ll ans = 0;
    REP (i, n) {
        REP (j, i) {
            int mn = 0x3f3f3f3f;
            for (int k=0; k<n; k++) {
                if (k != i && k != j) {
                    mn = min(mn, dis[i][k]+dis[k][j]);
                }
            }
            if (mn < dis[i][j]) {
                no_ans = true;
            } else if (mn > dis[i][j]) {
                ans += dis[i][j];
            }
        }
    }

    cout << (no_ans ? -1 : ans) << endl;

}
