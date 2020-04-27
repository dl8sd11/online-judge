#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3","unroll-loops")
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

const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
vector<pair<ll,ll> > pts;
set<pair<ll,ll> > can;

#define SQ(i) (1.0*(i)*(i))
/*********************GoodLuck***********************/
int main () {
    IOS();

    while (cin >> n) {
        pts.clear();
        can.clear();

        REP (i, n) {
            ll x, y;
            cin >> x >> y;
            pts.emplace_back(x, y);
        }

        sort(pts.begin(),pts.end());

        double mn = 1e18;

        int j = 0;
        REP (i, SZ(pts)) {
            ll x, y;
            tie(x, y) = pts[i];

            ll lim = ceil(mn) + 1;
            while (j<i && x-pts[j].first>lim) {
                can.erase({pts[j].second,pts[j].first});
                j++;
            }
            auto lb = can.lower_bound({y-lim,-INF});
            auto ub = can.lower_bound({y+lim,INF});

            for (auto it=lb;it!=ub;it++) {
                double cur = SQ(x-it->second) + SQ(y-it->first);
                mn = min(mn, sqrt(cur));
            }
            can.insert({y,x});
        }

        cout << fixed << setprecision(6) << mn << endl;
    }
}
