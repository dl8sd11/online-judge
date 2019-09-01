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
const int MAXN = 100005;
const int MAXD = 51;
 
int n, m, d, dp[MAXN * MAXD];
vector<int> edge[MAXN];
vector<int> redge[MAXN];
vector<int> dag[MAXN * MAXD];
bool vis[MAXN][MAXD], open[MAXN][MAXD];

int nxt[51], lst[51];
vector<pii> topo;
 

inline int reg (int x) {
    return x >= d ? x - d: x;
}
void dfs1 (int nd, int day) {
    vis[nd][day] = true;
    for (auto p : edge[nd]) {
        if (!vis[p][nxt[day]]) {
            dfs1(p, nxt[day]);
        }
    }
    topo.eb(nd, day);
}
 
int ccid[MAXN][MAXD], ccval[MAXN*MAXD], ccnt;
vector<int> mus;
void dfs2 (int nd, int day) {
    ccid[nd][day] = ccnt;
    if (open[nd][day]) {
        mus.eb(nd);
    }
    vis[nd][day] = false;
    for (auto p : redge[nd]) {
        if (vis[p][lst[day]]) {
            dfs2(p, lst[day]));
        }
    }
}
 
int solve (int id) {
    if (dp[id] != -1) {
        return dp[id];
    }
 
    dp[id] = 0;
    for (auto v : dag[id]) {
        dp[id] = max(dp[id], solve(v));
    }
    return dp[id] += ccval[id];
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    MEM(dp, -1);

    cin >> n >> m >> d;
    REP (i, d) {
        nxt[i] = (i + 1) % d;
        lst[i] = (i-1+d) % d;
    }
    REP (i, m) {
        int f, t;
        cin >> f >> t;
        REP (j, d) {
            edge[f].eb(t);
            redge[t].eb(f);
        }
    }
 
    REP1 (i, n) {
        REP (j, d) {
            char c;
            cin >> c;
            open[i][j] = c == '1';
        }
    }
 
    dfs1(1, 0);
    
    debug(topo);
    RREP (i, SZ(topo)-1) {
        if (vis[topo[i].X][topo[i].Y]) {
            ccnt++;
            dfs2(topo[i].X, topo[i].Y);
            sort(ALL(mus));
            ccval[ccnt] = unique(ALL(mus)) - mus.begin();
            mus.clear();
        }
    }
    topo.clear();
    topo.shrink_to_fit();
 
    pary(ccval, ccval+ccnt);
 
    REP1 (i, n) {
        redge[i].clear();
        redge[i].shrink_to_fit();
    }
    
    REP1 (i, n) {
        REP (j, d) {
            for (auto e : edge[i]) {
                if (ccid[i][j] != iNF && ccid[e][nxt[j]] != iNF) {
                    if (ccid[i][j] != ccid[e][nxt[j]]) {
                        dag[ccid[i][j]].eb(ccid[e][nxt[j]]);
                    }
                }
            }
        }
    }

    
 
    cout << solve(ccid[1][0]) << endl;
    return 0;
}