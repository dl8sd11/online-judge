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
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int q;

ll dp[61][2], x;

ll solve (ll lim, ll d, bool bd) {
//    debug(lim,d,bd);
    if (d == -1) {
        return 1;
    }
    if (dp[d][bd] != -1) {
        return dp[d][bd];
    }
    ll res = 0;
    REP (c, 2) {
        if ((((x>>d)&1) & c) == ((x>>d)&1)) {
            if ((!bd) || ((lim>>d)&1) >= c) {
                res += solve(lim,d-1,bd && ((lim>>d)&1) == c);
            }
        }
    }
//    debug(d, bd, lim,res);
    return dp[d][bd] = res;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> q;
    while (q--) {
        ll a, b;
        cin >> a >> b >> x;
        memset(dp, -1, sizeof(dp));
        ll rb = solve(b, 60, true);
        memset(dp, -1, sizeof(dp));
        ll ra = solve(a-1, 60, true);
        cout << rb-ra << endl;
    }
}

