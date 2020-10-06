#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double, double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) static_cast<int>(i.size())
#define FOR(i, j, k, in) for (int i=j; i < (k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j; i >= (k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(), _a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
template<typename T, typename S>
istream &operator >> (istream &is, pair<T, S> &p) {
    return is >> p.X >> p.Y;
}
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do {\
    fprintf(stderr, "%s - %d (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<" ,"; _do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << "," << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":",")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,2> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,3> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,4> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,5> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const set<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s, const map<_a,_b> &_c) {return _OUTC(_s,ALL(_c));}
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
const ll MAXN = 4005;


ll mypow(ll a,ll b){
	ll res=1LL;
	while(b){
		if(b&1) res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}

int lev[MAXN], ecnt, head[MAXN], cur[MAXN];
int n, k;

struct Graph {
    int f, t, cap, flow, nxt;
} G[100004];

void add_edge (int f, int t, int cap) {
#ifdef uta
    cout << "build: " <<  f << " " << t << " " << cap << endl;
#endif
    G[ecnt] = {f,t, cap, 0, head[f]};
    head[f] = ecnt++;
    G[ecnt] = {t,f, 0, 0, head[t]};
    head[t] = ecnt++;
}

int dfs (int nd, int t, int lim) {
    if (nd == t || lim == 0) return lim;
    for (int &i=cur[nd];i!=-1; i=G[i].nxt) {
        int x = G[i].t;
        if (G[i].cap > G[i].flow && lev[x] == lev[nd] + 1) {
            int df = dfs(x, t, min(lim, G[i].cap-G[i].flow));
            if (df) {
                G[i].flow += df;
                G[i^1].flow -= df;
                return df;
            }
        }
    }
    return 0;
}

bool bfs (int s, int t) {
    queue<int> q;
    q.emplace(s);
    memset(lev, -1, sizeof(lev));
    lev[s] = 0;

    while (q.size()) {
        int nd = q.front();
        q.pop();
        if (nd == t) {
            break;
        }
        for (int i=head[nd]; i!=-1; i=G[i].nxt) {
            if (G[i].cap > G[i].flow && lev[G[i].t] == -1) {
                lev[G[i].t] = lev[nd] + 1;
                q.emplace(G[i].t);
            }
        }
    }
    return lev[t] != -1;
}

int dinic (int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        int df = 0;
        for (int i=0; i<=t; i++) {
            cur[i] = head[i];
        }
    //    cerr << "die" << endl;
        while (df = dfs(s, t, 0x3f3f3f3f)) {
            flow += df;
        }
    }
    return flow;
}

#define X first
#define Y second
int a[MAXN], xr[MAXN], deg[MAXN];
vector<pii> edge[MAXN];
vector<vector<int> > mat;
int main(){
	IOS();
    cin >> n >> k;
    mat.resize(n);
    memset(head, -1, sizeof(head));
    for (int i=0; i<n; i++) {
        int m;
#ifdef tmd
        a[i] = (i==n-1 ? 1 : i+2); 
        m = 5;
#else
        cin >> a[i] >> m;
#endif
        a[i]--;
        mat[i].resize(m);
        for (int j=0; j<m; j++) {
#ifdef tmd
            mat[i][j] = rand() % 1000;

#else
            cin >> mat[i][j];
#endif
        }
        edge[i].eb(a[i], i);
        edge[a[i]].eb(i, i);
    }

    queue<int> bfs;
    vector<int> cyc(n, 1);
    for (int i=0; i<n; i++) {
        deg[i] = SZ(edge[i]);
        if (deg[i] == 1) {
            cyc[i] = false;
            bfs.emplace(i);
        }
    }
    int sz = n;
    while (bfs.size()) {
        int c = bfs.front();
        bfs.pop();
        sz--;
        for (auto v : edge[c]) {
            if (--deg[v.X] == 1) {
                bfs.emplace(v.X);
                cyc[v.X] = false;
            }
        }
    }


    vector<vector<int> > wk(k);
    map<int,int> color;
    int cc = 0;

    vector<int> wkm(k);
    for (int i=0; i<k; i++) {
        int d;
#ifdef tmd
        d = rand() % 1000;
#else
        cin >> d;
#endif
        if (color.count(d) == 0) color[d] = cc++;
        wkm[i] = d;
        wk[color[d]].eb(i);
    }

    for (int i=0; i<k; i++) {
        add_edge(0, i+1, SZ(wk[i]));
    }

    for (int i=0; i<n; i++) {
        if (cyc[i]) {
            add_edge(i+k+1, k+n+2, 1);
        } else {
            add_edge(i+k+1, k+n+3, 1);
        }
        for (int d : mat[i]) {
            if (color.count(d)) add_edge(1+color[d], i+k+1, 1);
        }
    }

    add_edge(k+n+2, k+n+3, sz - 1);
    int res = dinic(0, k+n+3);
    if (res != n-1) {
        assert(res < n-1);
        cout << -1 << endl;
        return 0;
    } 

    vector<pii> ans(k);

    int ccv = 0, tcv = 0;
    for (int i=0; i<ecnt; i++) {
        if (G[i].f <= k && G[i].t > k) {
            if (G[i].flow > 0) {
                assert(G[i].flow == 1);
                int u = G[i].t - k - 1;
                int v = a[u];
                int w = wk[G[i].f - 1].back();
                wk[G[i].f - 1].pop_back();
                ans[w] = {u+1, v+1};
                if (cyc[u]) ccv++;
                else tcv++;
            }
        }

    }

    assert(ccv == sz - 1);
    assert(tcv == n - sz);
    for (auto p : ans) {
        cout << p.X << " " << p.Y << endl;
    }
	
	return 0;
}
