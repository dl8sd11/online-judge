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

int n, m, cnt[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        if (v == 1 || v == n) {
            cnt[u]++;
        }
        if (u == 1 || u == n) {
            cnt[v]++;
        }
    }

    bool ans = false;
    for (int i=2; i<n;i++) {
        ans |= cnt[i] == 2;
    }

    cout << (ans ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    return 0;
}
