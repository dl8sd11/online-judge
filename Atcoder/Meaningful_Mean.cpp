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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

ll n, k, a[MAXN];
tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> st;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;

    ll sum = 0;
    st.insert(0);

    ll ans = 0;
    REP (i, n) {
        cin >> a[i];
        a[i] -= k;
        sum += a[i];
        ans += st.order_of_key(sum + 1);
        debug(sum, ans);
        st.insert(sum);
    }

    cout << ans << endl;
    return 0;
}
