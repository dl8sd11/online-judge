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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"("<<v.first<<","<<v.second<<")";}
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

int n;
vector<pair<int,int> > pts;
vector<pair<int,int> > hull;

typedef pair<int,int> pii;
pii operator - (const pii &p1, const pii &p2) {
    return {p1.first-p2.first,p1.second-p2.second};
}

ll operator ^ (const pii &p1, const pii &p2) {
    return 1LL*p1.first*p2.second - 1LL*p1.second*p2.first;
}

void build_hull () {
    for (auto p : pts) {
        while (SZ(hull)>=2 && ((p-hull.back())^(p-hull[SZ(hull)-2])) < 0) {
            hull.pop_back();
        }
        hull.emplace_back(p);
    }

    debug(hull);
}

ll get_res (ll l, ll r, ll x) {
    if (l == r) {
        return hull[l].second * 100000LL;
    }
    ll a = hull[l].second;
    ll b = hull[r].second;
    l = x - hull[l].first;
    r = hull[r].first - x;
    return (a*r + b*l)*100000 / (l+r);
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    #ifndef tmd

    freopen("balance.in","r",stdin);
    freopen("balance.out","w",stdout);

    #endif // tmd

    cin >> n;
    pts.emplace_back(0, 0);
    REP1 (i, n) {
        int d;
        cin >> d;
        pts.emplace_back(i, d);
    }
    pts.emplace_back(n+1, 0);

    build_hull();

    int l = 0, r = 0;
    REP1 (i, n) {
        while (hull[l+1].first <= i) {
            l++;
        }
        while (hull[r].first < i) {
            r++;
        }
        cout << get_res(l, r, i) << endl;
    }
}
