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

const int MAXN = 100005;
const ll MOD = 1000000007;


/*
15
1 1 1 0 0 1 0 1 1 0 0 1 0 1 1
*/
int n, sum;
vector<int> a;
ll test (int len) {
    if (len == 1) {
        return MOD*MOD;
    }
    ll ret = 0;
    REP (i, sum / len) {
        for (int j=0; j<len; j++) {
            // debug(i*len+j, i*len+len/2);
            ret += abs(a[i*len+j] - a[i*len+len/2]);
        }
    }

    debug(len, ret);
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int d;
        cin >> d;
        if (d) {
            a.emplace_back(i);
        }
        sum += d;
    }
    if (sum == 1) {
        cout << -1 << endl;
    } else {
        ll ans = test(sum);
        for (int i=2; i*i<=sum; i++) {
            if (sum % i == 0) {
                ans = min(ans, test(i));
                ans = min(ans, test(sum/i));
            }
        }
        cout << ans << endl;
    }
}
