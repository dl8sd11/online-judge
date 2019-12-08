#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 300005;
const ll MOD = 1000000007;

int t, n, a[MAXN], dp[MAXN], L[MAXN], R[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;

        vector<int> val;
        REP (i, n) {
            cin >> a[i];
            val.emplace_back(a[i]);
        }

        sort(val.begin(), val.end());
        val.resize(unique(val.begin(),val.end())-val.begin());

        int m = SZ(val);
        fill(L, L+m, n);
        fill(R, R+m, -1);
        for (int i=0; i<n; i++) {
            a[i] = lower_bound(val.begin(), val.end(), a[i])-val.begin();
            R[a[i]] = max(R[a[i]], i);
            L[a[i]] = min(L[a[i]], i);
        }

        int ans = m - 1;

        dp[0] = 1;
        for (int i=1; i<m; i++) {
            if (L[i] > R[i-1]) {
                dp[i] = dp[i-1] + 1;
            } else {
                dp[i] = 1;
            }
            ans = min(ans, m - dp[i]);
        }

        cout << ans << endl;
    }

}
