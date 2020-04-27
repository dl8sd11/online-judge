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
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &v) {
    return os << "{" << v.X << "," << v.Y << "}" << endl;
}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

vector<pii> pts, hull;

pii operator - (const pii &p1, const pii &p2) {
    return {p1.X-p2.X, p1.Y-p2.Y};
}

ll operator * (const pii &p1, const pii &p2) {
    return 1LL*p1.X*p2.Y - 1LL*p1.Y*p2.X;
}

int n;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    for (int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;
        pts.eb(x, y);
    }

    sort(ALL(pts));

    for (int i=0; i<SZ(pts); i++) {
        while (SZ(hull) >= 2 && (pts[i]-hull.back()) * (hull[SZ(hull)-2]-hull.back()) >= 0) {
            hull.pop_back();
        }
        hull.eb(pts[i]);
    }
    debug(hull);
    int sz = SZ(hull);
    for (int i=SZ(pts)-1; i>=0; i--) {
        while (SZ(hull) - sz >= 1 && (pts[i]-hull.back()) * (hull[SZ(hull)-2]-hull.back()) >= 0) {
            debug(i);
            debug(hull.back());
            hull.pop_back();
        }
        hull.eb(pts[i]);
    }
    hull.pop_back();
    debug(hull);
    for (auto v : hull) {
        cout << v.X << " " << v.Y << endl;
    }

    double ans = 0;
    for (int i=2; i<SZ(hull); i++) {
        ans += (hull[i] - hull[0]) * (hull[i-1] - hull[0]);
    }

    cout << hull.size() << endl;
    cout << ans / 2 << endl;
}

