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

int k, n;

/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> k >> n;

    vector<int> ans;

    if (k & 1) {
        ans = vector<int>(n, (k+1)/2);
        REP (i, n/2) {
            if (ans.back() == 1) {
                ans.pop_back();
            } else {
                ans.back()--;
                while (ans.size() < n) {
                    ans.emplace_back(k);
                }
            }
        }
    } else {
        ans = vector<int>(n, k);
        ans.front() = k/2;
    }

    REP (i, SZ(ans)) {
        cout << ans[i] << " \n"[i==SZ(ans)-1];
    }
}
