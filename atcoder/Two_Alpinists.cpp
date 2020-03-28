#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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

int n, a[MAXN], b[MAXN];

int res[MAXN], lim[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    int bst = 0;

    memset(lim, 0x3f, sizeof(lim));
    REP (i, n) {
        cin >> a[i];
        if (a[i] > bst) {
            res[i] = a[i];
            bst = a[i];
        } else {
            lim[i] = bst;
        }
    }

    pary(res, res+n);
    bst = 0;

    REP (i, n) {
        cin >> b[i];
    }
    for (int i=n-1; i>=0; i--) {
        if (b[i] > bst) {
            if (res[i] == 0 || res[i] == b[i]) {
                res[i] = b[i];
                bst = b[i];
            } else {
                cout << 0 << endl;
                return 0;
            }
        } else {
            lim[i] = min(lim[i], bst);
        }
    }

    pary(res, res+n);
    pary(lim, lim+n);
    ll ans = 1;
    REP (i, n) {
        if (res[i] == 0) {
            ans = ans * lim[i] % MOD;
        } else if (res[i] > lim[i]) {
            ans = 0;
        }
    }

    cout << ans << endl;


}
