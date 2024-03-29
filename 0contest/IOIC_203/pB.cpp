#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
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
#define TIME(i) Timer i(#i)
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
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 5003;


/*
10 4
4 7 2
4 8 2
-2 -10 -3
-4 -5 -1

d[7]-d[3] <= 2
d[8]-d[3] <= 2
d[10]-d[1] >= 3
d[5]-d[3] >= 1
*/

int n, q;

struct Edge {
    ll f, t, w;
};
vector<Edge> edges;
void gt (ll l, ll r, ll lim) {
    edges.pb({r,l-1,-lim});
}

void le (ll l, ll r, ll lim) {
    edges.pb({l-1,r,lim});
}

ll dis[MAXN];
bool nsol = false;
void solve () {

    MEM(dis, INF);
    dis[n+1] = 0;
    REP (i, n) {
        for (auto E : edges) {
            dis[E.t] = min(dis[E.t], dis[E.f]+E.w);
        }
    }

    for (auto E : edges) {
            debug(E.f, E.t, E.w);
    }

    for (auto E : edges) {
        if (dis[E.t] > dis[E.f] + E.w) {
            debug(E.f, E.t, E.w);
            debug(dis[E.f], dis[E.t]);
            nsol = true;
        }
    }
}
/*
3 1
-2 -3 -1
*/
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> q;
    edges.pb({n+1,0,0});
    REP1 (i, n) {
        edges.pb({n+1,i,0});
        gt(i,i,0);
        le(i,i,1);
    }
    while (q--) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 0) {
            gt(-u,-v,-w);
        } else {
            le(u,v,w);
        }
    }

    solve();
    pary(dis, dis+n+1);
    debug(nsol);

    if (nsol) {
        cout << -1 << endl;
    } else {
        REP1 (i, n) {
            dis[i] -= dis[0];
        }
        dis[0] = 0;
        REP1 (i, n) {
            cout << dis[i] - dis[i-1] << " \n"[i==n];
        }
    }

    return 0;
}
