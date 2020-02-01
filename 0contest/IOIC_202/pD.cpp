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
const int MAXN = 200005;
const int MAXLG = __lg(200005) + 3;

int n, m, q;
int mx[MAXN], sz[MAXN];
vector<int> ans[MAXN], edge[MAXN];

int anc[MAXLG][MAXN];
void dfs (int nd, int par) {
    sz[nd] = 1;
    mx[nd] = 0;
    anc[0][nd] = par;

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
            sz[nd] += sz[v];
            mx[nd] = max(mx[nd], sz[v]);
        }
    }
}


void build_lca () {
    REP1 (i, MAXLG-1) {
        REP1 (j, MAXN-1) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

void build (int nd) {
    int p = nd;
    if (sz[p]/2 < mx[nd]) {
        for (int i=MAXLG-1; i>=0;i--) {
            int fut = anc[i][p];
            if (fut != 0 && sz[fut]/2 < mx[nd]) {
                p = fut;
            }
        }

        p = anc[0][p];
    }
    if (sz[p]/2 >= mx[nd]) {
        while (p != 0 && (sz[p]+1)/2 <= sz[nd]) {
            ans[p].eb(nd);
            p = anc[0][p];
        }
    }
}
/********** Good Luck :) **********/
int main () {
srand(279936);
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n-1) {
        int u, v;

    #ifdef tmd
        u = i + 2;
        v = rand() % (i+1) + 1;
    #else
        cin >> u >> v;
    #endif
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1, 0);
    build_lca();
    // pary(mx+1, mx+n+1);
    // pary(sz+1, sz+n+1);

    REP1 (i, n) {
        build(i);
    }

    REP1 (i, n) {
        debug(ans[i]);
        assert(ans[i].size() == 1 || ans[i].size() == 2);
        sort(ALL(ans[i]));

        REP (j, SZ(ans[i])) {
            cout << ans[i][j] << " \n"[j==SZ(ans[i])-1];
        }
    }
    return 0;
}
