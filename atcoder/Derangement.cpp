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

int n, p[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> p[i];
    }

    int ans = 0;
    REP1 (i, n) {
        if (p[i] == i) {
            ans++;
            if (i == n) {
                swap(p[i], p[i-1]);
            } else {
                swap(p[i], p[i+1]);
            }
        }
    }

    cout << ans << endl;
    return 0;
}
