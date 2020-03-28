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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n, z, a[MAXN], sm[2003];
namespace SMALL {
    int eval () {
        int res = 0;
        REP1 (i, n) {
            int mn = sm[i], mx = sm[i], j;
            for (j=0; ; j++) {
                mn = min(mn, sm[i+j]);
                mx = max(mx, sm[i+j]);

                if (mn == i && mx == i+j) {
                    break;
                }
            }

            i = i+j;
            res++;
        }
        return res;
    }

    void solve () {
        REP1 (i, n) {
            cin >> sm[i];
        }
        cout << eval() << endl;
        REP (i, z-1) {
            int u, v;
            cin >> u >> v;
            swap(sm[u], sm[v]);
            cout << eval() << endl;
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> z;

    if (n <= 2000) {
        SMALL::solve();
    }
}
