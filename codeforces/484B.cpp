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

const int MAXN = 2000006;
const ll MOD = 1000000007;

int n, a[MAXN], b[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i];
    }
    sort(a, a+n);
    n = unique(a, a+n)-a;
    a[n] = MAXN;
    for (int i=0; i<n;i++) {
        for (int j=a[i]; j<a[i+1]; j++) {
            b[j] = a[i];
        }
    }

    int ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=a[i]; j<MAXN; j+=a[i]) {
            int mx = b[j-1];
            if (mx >= a[i]) {
                ans = max(mx % a[i], ans);
            }
        }
    }

    cout << ans << endl;

    return 0;
}
