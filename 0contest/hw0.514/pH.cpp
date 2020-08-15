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
const ll MAXN = 2003;

struct Dinic{
    struct Edge{
        int to, rev; ll cap, flow=0;
        Edge(int to,int rev, ll cap) : to(to), rev(rev), cap(cap) {}
    };

    vector<vector<Edge> > g; 
    int n;
    int s, t;
    vector<int> level, ptr;
    Dinic(int n, int s, int t):n(n),s(s),t(t){
        level.resize(n,-1); ptr.resize(n); g.resize(n);
    }
    void add(int v, int u, ll cap){
        g[v].pb({u,SZ(g[u]),cap}); 
        g[u].pb({v,SZ(g[v])-1,0});
    }
    bool bfs(){ // Build layers with edges on the residual graph that aren't full
        queue<int> q({s});
        level[s] = 0;
        while (!q.empty() && level[t] == -1){
            int v = q.front(); q.pop();
            for (auto &e : g[v]){
                if (e.cap - e.flow ==0) continue;
                int u = e.to;
                if (level[u]==-1){
                    level[u] = level[v]+1; q.push(u);
                }
            }
        } return level[t]!=-1;
    }
    ll dfs(int v, ll amt){ // Returns flow amount of any flow on bfs graph
        if (amt == 0 || v==t) return amt;
        for (; ptr[v] <SZ(g[v]); ptr[v]++){
            Edge &e = g[v][ptr[v]]; 
            int u = e.to;
            if (level[u] == level[v]+1){
                ll tt = dfs(u,min(amt, e.cap - e.flow));
                if (tt==0) continue;
                e.flow+=tt; g[e.to][e.rev].flow-=tt; return tt;
            }
        } return 0;
    }
    ll mf(){
        ll re = 0;
        while (bfs()){
            while (ll amt = dfs(s,INF)) re += amt; // Basically ford fulkerson, but on layered graph
            fill(ALL(level), -1); fill(ALL(ptr), 0);
        } return re;
    }
};

vector<pii> d[MAXN];
vector<int> ans;
int ptr[MAXN];

void dfs (int nd) {
    for (int &i=ptr[nd]; i<SZ(d[nd]); ) {
        auto p = d[nd][i];
        i++;
        dfs(p.X);
        ans.eb(p.Y);
    }
}
int main () {
    TIME(main);
    IOS();

    int n, m;
    array<int,4> edge[MAXN];

    cin >> n >> m;

    vector<int> deg(n, 0);
    for (int i=0; i<m; i++) {
        for (int j=0; j<4; j++) {
            cin >> edge[i][j];
        }
        deg[--edge[i][0]]++, deg[--edge[i][1]]++;
    }

    for (int i=0; i<n; i++) {
        if (deg[i] & 1) {
            cout << "NIE" << endl;
            return 0;
        }
    }

    int v = 2 + n + m;
    debug(deg);


    int L = 0, R = 1000;
    while (L < R - 1) {
        int M = (L + R) >> 1;

        Dinic mf(v, 0, 1);
        for (int i=0; i<m; i++) {
            int f = edge[i][0];
            int t = edge[i][1];
            int l = edge[i][2];
            int p = edge[i][3];

            int eid = 2 + i;
            int fid = 2 + m + f;
            int tid = 2 + m + t;

            mf.add(0, eid, 1);
            if (l <= M) {
                mf.add(eid, fid, 1);
            }
            if (p <= M) {
                mf.add(eid, tid, 1);
            }
        }
        for (int i=0; i<n; i++) {
            mf.add(2+m+i, 1, deg[i]/2);
        }

        if (mf.mf() == m) {
            R = M;
        } else {
            L = M;
        }
    }

    {
        Dinic mf(v, 0, 1);
        for (int i=0; i<m; i++) {
            int f = edge[i][0];
            int t = edge[i][1];
            int l = edge[i][2];
            int p = edge[i][3];

            int eid = 2 + i;
            int fid = 2 + m + f;
            int tid = 2 + m + t;

            mf.add(0, eid, 1);
            if (l <= R) {
                mf.add(eid, fid, 1);
            }
            if (p <= R) {
                mf.add(eid, tid, 1);
            }
        }
        for (int i=0; i<n; i++) {
            mf.add(2+m+i, 1, deg[i]/2);
        }

        int res = mf.mf();
        for (int i=0; i<m; i++) {
            for (auto E: mf.g[i+2]) {
                if (E.to == 0) {
                    continue;
                }
                if (E.flow) {
                    int u = E.to - 2 - m;
                    int v = edge[i][0] ^ edge[i][1] ^ u;

                    d[u].eb(v, i+1);
                }
            }
        }

        REP (i, n) {
            debug(d[i]);
        }
    }

    cout << R << endl;

    dfs(0);
    reverse(ALL(ans));
    m = SZ(ans);
    for (int i=0; i<m; i++) {
        cout << ans[i] << " \n"[i==m-1];
    }
    return 0;
}
