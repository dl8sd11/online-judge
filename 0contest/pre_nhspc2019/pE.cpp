#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("03","unroll-loops")
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define MEM(a,b) memset(a,(b),sizeof(a))
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d: (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &p){return os<<"("<<p.first<<","<<p.second<<")";}
template<typename IT> ostream &_printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        os << (it==bg?"":",") << *it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &vec) {return _printRng(os, vec.begin(),vec.end());}
template<typename IT> void pary (IT bg, IT ed) {_printRng(cerr,bg,ed);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXK = 102;
const int MAXN = 100005;

int n, k;
ll dp[MAXK], a[MAXN], x[MAXK];

int main () {
    IOS();

    cin >> n >> k;
    n--;

    REP1 (i, n) {
        cin >> a[i];
    }
    REP1 (j, k) {
        cin >> x[j];
    }

    sort(x+1, x+k+1, [](int i1,int i2) {return i1 > i2;});
    pary(x, x+k+1);

    ll ans = 0;
    REP1 (i, n) {
        for (int j=k; j>=1; j--) {
            dp[j] = max(dp[j-1]+x[j], dp[j]+a[i]);
        }
        dp[0] = max(dp[0]+a[i], 0LL);

        REP (j, k+1) {
            ans = max(ans, dp[j]);
        }
    }

    cout << ans << endl;
}
