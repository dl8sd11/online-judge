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

const int MAXN = 100005;
const int MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int t, n;

ll cob(ll x) {
    ll ans = 1;
    REP1 (i,x) {
        ans *= (i+x);
    }
    REP1 (i, x) {
        ans /= i;
    }
    return ans;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;

//        ll sum = 0;
//        REP1 (i, n) {
//            sum += cob(i-1) * cob(n-i);
//        }

        ll bs = 4;
        int res = 1;

        int ep = n-1;
        while (ep) {
            if (ep&1) {
                res = res * bs % MOD;
            }
            ep >>= 1;
            bs = bs * bs % MOD;
        }


        cout << res << endl;

    }

}
