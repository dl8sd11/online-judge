#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <sstream>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>
#include <assert.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD=1000000007;
const ll MAXN=1e3+5;

#define SQ(i) (i)*(i)


struct vil {
    double x,y,a;
};

vil v[MAXN];
double dis[MAXN][MAXN];
double cost[MAXN][MAXN];
bool vis[MAXN];
double mdis[MAXN];
ll n;

double kru (double t) {
    double sum = 0;
    MEM(vis,0);
    REP (i,n) mdis[i] = 1e19;
    mdis[0] = 0;
    
    REP (i,n) {
        ll mkey = -1;
        REP (j,n) {
            if (!vis[j] && (mkey == -1 || mdis[j] < mdis[mkey]))mkey = j;
        }

        vis[mkey] = 1;
        sum += mdis[mkey];

        REP (j,n) {
            if (j != mkey) {
                mdis[j] = min(mdis[j],cost[mkey][j] - t * dis[mkey][j]);
            }
        }
    }    

    return sum;
}


/********** Good Luck :) **********/
int main()
{
    IOS();
    while (cin>>n && n) {

        REP (i,n) {
            double x,y,a;
            cin>>x>>y>>a;
            v[i].x = x;
            v[i].y = y;
            v[i].a = a;
        }

        REP (i,n) {
            REP (j,i) {
                cost[i][j] = abs(v[i].a-v[j].a);
                cost[j][i] = abs(v[i].a-v[j].a);
                dis[j][i] = sqrt(SQ(v[i].x-v[j].x)+SQ(v[i].y-v[j].y));
                dis[j][i] = sqrt(SQ(v[i].x-v[j].x)+SQ(v[i].y-v[j].y));
            }
        }

        double L = 0,R = 1000000003;
        while (L < R - 1e-7) {
            double mid = (L+R)/2;
            if (kru(mid) < 0) {
                R = mid;
            } else {
                L = mid;
            }
        }

        cout << fixed << setprecision(3) << R << endl;
    }
    return 0;
}
