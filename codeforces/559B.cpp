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

string a, b;

void solve (string &str, int l, int r) {
    if (r - l & 1) {
        return;
    } else {
        int m = (l + r) >> 1;
        solve(str, l, m);
        solve(str, m, r);
        bool flag = false;
        REP (i, (r-l)/2) {
            if (str[l+i] < str[m+i]) {
                break;
            } else if (str[l+i] > str[m+i]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            REP (i, (r-l)/2) {
                swap(str[l+i], str[m+i]);
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> a >> b;

    solve(a, 0, SZ(a));
    solve(b, 0, SZ(b));

    cout << (a == b ? "YES" : "NO") << endl;
    return 0;
}
