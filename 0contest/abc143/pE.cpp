#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
const ll MAXN = 302;

struct Dis {
    int fll, rem;
    bool operator < (const Dis &dcp) const {
        if (fll != dcp.fll) {
            return fll > dcp.fll;
        } else {
            return rem < dcp.rem;
        }
    }

    void init () {
        fll = iNF, iNF;
    }
};

Dis dis[MAXN][MAXN];
int n, m, l;
bool vis[MAXN];
vector<pii> edg[MAXN];

void build (int st) {
    REP1 (i, n) {
        dis[st][i].init();
    }
    dis[st][st] = {0, l};
    priority_queue<pair<Dis,int> > pq;
    pq.emplace(dis[st][st], st);
    MEM(vis, 0);

    while (pq.size()) {
        pair<Dis,int> cur = pq.top();
        pq.pop();
        if (vis[cur.Y]) {
            continue;
        }
        vis[cur.Y] = true;

        for (auto e : edg[cur.Y]) {
            Dis nw;
            if (e.Y > cur.X.rem) {
                if (e.Y > l) {
                    continue;
                }
                nw = {cur.X.fll+1, l-e.Y};
            } else {
                nw = {cur.X.fll, cur.X.rem - e.Y};
            }
            if (dis[st][e.X] < nw) {
                dis[st][e.X] = nw;
                pq.emplace(dis[st][e.X], e.X);
            }
        }
    }

}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    cin >> n >> m >> l;
    REP (i, m) {
        int a, b, w;
        cin >> a >> b >> w;
        edg[a].emplace_back(b, w);
        edg[b].emplace_back(a, w);
    }

    REP1 (i, n) {
        build(i);
    }
    debug(dis[3][2].fll, dis[3][2].rem);

    int q;
    cin >> q;
    while (q--) {
        int s, t;
        cin >> s >> t;
        cout << (dis[s][t].fll == iNF ? -1 : dis[s][t].fll) << endl;
    }

    return 0;
}
