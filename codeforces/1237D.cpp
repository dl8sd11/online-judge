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

int n, a[MAXN*3], ans[MAXN];
vector<pair<int,int> > stk;
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;
    REP (i, n) {
        cin >> a[i];
        a[i+n] = a[i+n*2] = a[i];
    }

    stk.emplace_back(-1, n*3);
    int lst = 3*n;
    for (int i=n*3-1; i>=0; i--) {
        int l = 0, r = SZ(stk);
        while (l < r - 1) {
            int m = (l + r) >> 1;
            if (stk[m].first < (a[i]+1)/2) {
                l = m;
            } else {
                r = m;
            }
        }
        lst = min(lst, stk[l].second);

        if (i < n) {
            if (lst == 3*n) {
                ans[i] = -1;
            } else {
                ans[i] = lst - i;
            }
        }
        while (stk.back().first >= a[i]) {
            stk.pop_back();
        }
        stk.emplace_back(a[i], i);
    }

    REP (i, n) {
        cout << ans[i] << " \n"[i==n-1];
    }
}
