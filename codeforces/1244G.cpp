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

ll n, k;
bool vis[MAXN];
vector<int> ans2;
/*********************GoodLuck***********************/
int main () {
    IOS();

    while (cin >> n >> k) {
        memset(vis, 0, sizeof(bool)*(n+1));
        ll dl = k - (1 + n) * n / 2;
        if (dl < 0) {
            cout << -1 << endl;
        } else {
            ans2.resize(n);
            REP (i, n/2) {
                int ci = n/2-i;
                ll x = min(ll(n-i-ci), dl);
                dl -= x;
                ans2[n/2-i-1] = ci + x;
                vis[ci+x] = true;

            }

            int idx = 1;
            for (int i=n/2+1; i<=n; i++) {
                while (vis[idx]) {
                    idx++;
                }
                vis[idx] = true;
                ans2[i-1] = idx;
            }

            ll res = 0;
            REP (i, n) {
                res += max(i+1, ans2[i]);
            }
            cout << res << endl;
            #ifndef tmd
            REP1 (i, n) {
                cout << i << " \n"[i==n];
            }
            #endif

            set<int> rst;
            REP (i, n) {
                #ifdef tmd
                    rst.insert(ans2[i]);
                #else
                cout << ans2[i] << " \n"[i==n-1];
                #endif
            }

            #ifdef tmd
            debug(SZ(rst), *rst.begin(), *prev(rst.end()));
            #endif
        }
    }
    return 0;
}
