#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
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

const int MAXN = 1000005;
const ll MOD = 1000000007;
ld EPS = 1e-10;



int n;
vector<pair<ll,ll> > hull;

pll operator - (pll a, pll b) {
    return {a.X-b.X, a.Y-b.Y};
}
ll cs (pll a, pll b) {
    return a.X*b.Y - a.Y*b.X;
}

double ans[MAXN];
/*********************GoodLuck***********************/
int main () {

    scanf("%d", &n);

    ll sum = 0;

    hull.eb(0, 0);
    for (int i=1; i<=n; i++) {
        int x;
        scanf("%d", &x);
        sum += x;
        pll nw = {i, sum};
        while (SZ(hull)>=2 && cs(nw-hull.back(), hull[SZ(hull)-2]-hull.back()) <= 0) {
            hull.pop_back();
        }
        hull.eb(nw);
        debug(i);
    }

    for (int i=1; i<SZ(hull); i++) {
        for (int k=hull[i-1].X+1; k<=hull[i].X; k++) {
            printf("%.9f\n", (double)(hull[i].Y-hull[i-1].Y)/(hull[i].X-hull[i-1].X));
        }
    }




}
