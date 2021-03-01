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
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 302;

int n, m;
vector<pair<pii, pii> > blk;

set<int> xsplit, ysplit;
vector<pii> xseg, yseg;

struct Edge {
    int t, cap, flow, nxt;
};
vector<Edge> edge;
int head[MAXN];

void add_edge (int f, int t, int c) {
    debug(f, t, c);
    edge.pb({t, c, 0, head[f]});
    head[f] = SZ(edge) - 1;
    edge.pb({f, 0, 0, head[t]});
    head[t] = SZ(edge) - 1;
}

int lev[MAXN];

bool bfs (int f, int t) {
    MEM(lev, -1);
    queue<int> que;
    que.emplace(f);
    lev[f] = 0;

    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (int i=head[cur]; i!=-1; i=edge[i].nxt) {
            int x = edge[i].t;
            if (lev[x] == -1 && edge[i].flow < edge[i].cap) {
                lev[x] = lev[cur] + 1;
                que.emplace(x);
            }
        }
    }

    return lev[t] != -1;
}

int dfs (int t, int nd, int lim) {
    if (nd == t || lim == 0) {
        return lim;
    }

    for (int i=head[nd]; i != -1; i=edge[i].nxt) {
        int x = edge[i].t;
        if (lev[x] == lev[nd]+1 && edge[i].cap > edge[i].flow) {
            int d = dfs(t, x, min(lim, edge[i].cap - edge[i].flow));
            if (d) {
                edge[i].flow += d;
                edge[i^1].flow -= d;
                return d;
            }
        }
    }

    return 0;
}

int dinic (int f, int t) {
    int flow = 0;
    while (bfs(f, t)) {
        int df = -1;
        while (df = dfs(t, f, iNF)) {
            flow += df;
        }
    }

    return flow;
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    MEM(head, -1);

    cin >> n >> m;


    xsplit.insert(n);
    ysplit.insert(n);

    REP (i, m) {
        int xa, xb, ya, yb;
        cin >> xa >> ya >> xb >> yb;
        blk.eb(pii(xa, ya), pii(xb, yb));

        xsplit.insert(xa-1);
        xsplit.insert(xb);
        ysplit.insert(ya-1);
        ysplit.insert(yb);
    }

    int cx = 1, cy = 1;
    for (auto p : xsplit) {
        if (p >= cx) {
            xseg.eb(cx, p);
        }
        cx = p + 1;
    }

    for (auto p : ysplit) {
        if (p >= cy) {
            yseg.eb(cy, p);
        }
        cy = p + 1;
    }

    debug(xseg);
    debug(yseg);

    int mstart = 2, lstart = 2 + m, rstart = 2 + m + SZ(xseg);
    int src = 0, des = 1;

    REP (i, m) {
        REP (j, SZ(xseg)) {
            auto rng = xseg[j];
            if (blk[i].X.X <= rng.X && rng.Y <= blk[i].Y.X) {
                add_edge(lstart+j, mstart+i, iNF);
            }
        }

        REP (j, SZ(yseg)) {
            auto rng = yseg[j];
            if (blk[i].X.Y <= rng.X && rng.Y <= blk[i].Y.Y) {
                add_edge(mstart+i, rstart+j, iNF);
            }
        }
    }

    REP (i, SZ(xseg)) {
        add_edge(0, lstart+i, xseg[i].Y-xseg[i].X+1);
    }
    REP (i, SZ(yseg)) {
        add_edge(rstart+i, 1, yseg[i].Y-yseg[i].X+1);
    }

    cout << dinic(src, des) << endl;
    return 0;
}
