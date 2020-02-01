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

int n, s, cp[MAXN], iv[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> s;

    int mx = -1, ans = -1;
    REP1 (i, n) {
        cin >> cp[i] >> iv[i];
        int inc;
        if (iv[i] <= 29) {
            inc = 10;
        } else if (iv[i] <= 39) {
            inc = 50;
        } else {
            inc = 100;
        }
        int cur = cp[i] + (s / 1000) * inc;
        if (cur > ans) {
            mx = i;
            ans = cur;
        }
    }

    cout << mx << " " << ans << endl;

}
