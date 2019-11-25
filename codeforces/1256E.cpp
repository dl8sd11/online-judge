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

const int MAXN = 200005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, ans[MAXN], dp[MAXN], tr[MAXN];
pair<int,int> a[MAXN];

ll eval (int id) {
    return dp[id] - a[id+1].first;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a+1, a+n+1);

    dp[1] = dp[2] = INF;

    ll mnid = 0;
    for (int i=3; i<=n; i++) {
        if (eval(i-3) < eval(mnid)) {
            mnid = i-3;
        }
        dp[i] = eval(mnid) + a[i].first;
        tr[i] = mnid;
    }

    int x = n;
    int cnt = 0;
    while (x != 0) {
        cnt++;
        debug(x);
        for (int i=tr[x]+1; i<=x; i++) {
            ans[a[i].second] = cnt;
        }
        x = tr[x];
    }

    cout << dp[n] << " " << cnt << endl;
    REP1 (i, n) {
        cout << ans[i] << " \n"[i==n];
    }
}
