#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
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
const ull p[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

int t, mx;
ull n, ans;

void dfs (int idx, ull num, int divs, int limit) {
    if (num > n) {
        return;
    }
    if (divs > mx) {
        mx = divs;
        ans = num;
    } else if (divs == mx) {
        ans = min(ans, num);
    }

    for (int i=1; i<=limit; i++) {
        if (num > n/p[idx]) {
            break;
        }
        num *= p[idx];
        dfs(idx+1, num, divs*(1+i), i);
    }
}
/*********************GoodLuck***********************/
int main () {

    cin >> t;
    while (t--) {
        cin >> n;
        mx = 0;
        dfs(0, 1, 1, 100);
        cout << ans << " " << mx << endl;
    }
    return 0;
}
