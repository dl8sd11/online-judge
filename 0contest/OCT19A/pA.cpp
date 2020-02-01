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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int t, n, a, cnt[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;
        int ans = 0;
        memset(cnt, 0, sizeof(cnt));
        REP (i, n) {
            cin >> a;
            ans = max(ans, cnt[a]);
            for (int j=1; j*j<=a; j++) {
                if (a % j == 0) {
                    cnt[j]++;
                    if (j*j!=a) {
                        cnt[a/j]++;
                    }
                }
            }
        }

        cout << ans << endl;
    }

    return 0;
}

