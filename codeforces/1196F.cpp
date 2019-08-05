#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pii;
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
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 1003;

int n, m, k;

struct Edge {
    int u, v;
    ll w;
    bool operator < (Edge &ec) {
        return w < ec.w;
    }
};
vector<Edge> edge;

vector<int> nodes_val;


vector<pii> G[MAXN];

vector<ll> ans;
ll dis[MAXN][MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m >> k;
    REP (i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        edge.pb({u, v, w});
    }

    sort(ALL(edge));

    MEM(dis, INF);
    REP (i, min(SZ(edge), k)) {
        Edge &edg = edge[i];
        nodes_val.eb(edg.u);
        nodes_val.eb(edg.v);
    }

    sort(ALL(nodes_val));
    nodes_val.resize(unique(ALL(nodes_val)) - nodes_val.begin());

    REP (i, min(SZ(edge), k)) {
        Edge &edg = edge[i];
        int u = lower_bound(ALL(nodes_val), edg.u) - nodes_val.begin();
        int v = lower_bound(ALL(nodes_val), edg.v) - nodes_val.begin();
        dis[u][v] = edg.w;
        dis[v][u] = edg.w;
    }

    REP (tr, SZ(nodes_val)) {
        REP (f, SZ(nodes_val)) {
            REP (t, SZ(nodes_val)) {
                if (dis[f][tr] != INF && dis[tr][t] != INF) {
                    dis[f][t] = min(dis[f][t], dis[f][tr] + dis[tr][t]);
                }
            }
        }
    }

    REP (f, SZ(nodes_val)) {
        REP (t, SZ(nodes_val)) {
            if (f < t && dis[f][t] != INF) {
                ans.eb(dis[f][t]);
            }
        }
    }

    assert(SZ(ans) >= k);
    sort(ALL(ans));
    debug(ans);

    cout << ans[k-1] << endl;

    return 0;
}
