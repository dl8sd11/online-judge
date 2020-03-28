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

int n;


vector<pair<ll,ll> > pts;

ll dis (pll a, pll b) {
    return (a.X-b.X)*(a.X-b.X) + (a.Y-b.Y)*(a.Y-b.Y);
}

pll operator - (pll a, pll b) {
    return {a.X-b.X, a.Y-b.Y};
}

ll dot (pll a, pll b) {
    return a.X*b.X + a.Y*b.Y;
}


/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int u, v;
        cin >> u >> v;
        pts.eb(u, v);
    }

    pts.eb(pts.front());

    if (n & 1) {
        cout << "No" << endl;
    } else {
        bool sm = true;
        REP (i, n/2) {
            if (dis(pts[i], pts[i+1]) != dis(pts[i+n/2], pts[i+n/2+1])) {
                sm = false;
            }
        }

        REP (i, n/2-1) {
            pll v1 = pts[i]-pts[i+1], v2 = pts[i+2]-pts[i+1];
            pll v3 = pts[i+n/2]-pts[i+n/2+1], v4 = pts[i+n/2+2]-pts[i+n/2+1];

            if (dot(v1, v2) != dot(v3, v4)) {
                sm = false;
            }
        }

        cout << (sm ? "Yes" : "No") << endl;
    }

}
