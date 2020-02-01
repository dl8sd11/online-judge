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


int n, a[MAXN];
int opt[MAXN], ans, sz;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i];
    }

    sz = 0;
    opt[0] = -1;

    memset(opt,0x3f3f3f3f,sizeof(int)*(n+1));
    REP (i, n) {
        int l = 0, r = sz+1;
        while (l < r - 1) {
            int m = (l + r) >> 1;
            if (a[i] > opt[m]) {
                l = m;
            } else {
                r = m;
            }
        }
        opt[r] = min(opt[r], a[i]);
        ans = max(r, ans);
        sz = max(sz, r);
        pary(opt,opt+sz);
    }

    cout << ans << endl;
}
