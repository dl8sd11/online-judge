#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define X first
#define Y second
#define MN(a,b) a=min(a,b)
#define MX(a,b) a=max(a,b)
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

const int MAXN = 202;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
typedef pair<int,int> pii;
pii p[MAXN];
/* TODO:
- build final state
- build distance
- build dp
- check perfectly symmetry
*/

struct State {
    int root, last, val;
};

void build_final (bool rev) {

}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    REP (i, n) {
        cin >> p[i].X >> p[i].Y;
    }

    ll ans = INF;
    REP (s, n) {
        MN(ans, solve(s));
    }

    cout << ans << endl;

}
