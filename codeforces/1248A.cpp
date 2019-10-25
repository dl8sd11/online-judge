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
const ll MOD = 1000000007;

int t, n, m, cnt[2][2];
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> t;
    while (t--) {
        memset(cnt, 0, sizeof(cnt));
        cin >> n;
        REP (i, n) {
            int d;
            cin >> d;
            cnt[0][d&1]++;
        }
        cin >> m;
        REP (i, m) {
            int d;
            cin >> d;
            cnt[1][d&1]++;
        }

        cout << ll(cnt[0][1])*(cnt[1][1]) + ll(cnt[0][0])*(cnt[1][0]) << endl;
    }
}
