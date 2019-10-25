#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 500005;

ll n;
map<ll, ll> ans;

ll solve (ll x) {
    if (x == 0) {
        return 1;
    }
    if (ans.count(x)) {
        return ans[x];
    } else {
        int mx = 0;
        REP (i, 62) {
            if (x & (1LL<<i)) {
                mx = i;
            }
        }
        debug(x, mx);
        return ans[x] = 2 * solve(x - (1LL<<mx));
    }
}

/****GOOD_LUCK****/
int main () {
    IOS();

    cin >> n;
    cout << solve(n) << endl;

    return 0;
}
