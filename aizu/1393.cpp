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
const ll MAXN = 102;

int n, m;
bool edge[MAXN][MAXN];
bool comp[MAXN][MAXN];
int deg[MAXN];
vector<pii> ans;

bool vis[MAXN];
void make_even (int nd) {
    vis[nd] = true;
    REP1 (i, n) {
        if (comp[nd][i] && !vis[i]) {
            make_even(i);
            if (deg[i] & 1) {
                deg[i]++;
                deg[nd]++;
                edge[i][nd] = true;
                edge[nd][i] = true;
                ans.eb(i, nd);
            }
        }
    }
}

void dfs (int nd, vector<int> &cur) {
    vis[nd] = true;
    cur.eb(nd);
    REP1 (i, n) {
        if (!vis[i] && edge[i][nd]) {
            dfs(i, cur);
        }
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> m;
    
    REP1 (i, n) {
        REP1 (j, n) {
            comp[i][j] = true;
        }
    }
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u][v] = true;
        edge[v][u] = true;
        comp[u][v] = false;
        comp[v][u] = false;
        deg[u]++;
        deg[v]++;
    }

    REP1 (i, n) {
        if (!vis[i]) {
            make_even(i);
            if (deg[i] & 1) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    MEM(vis, 0);
    vector<vector<int> > cc;
    REP1 (i, n) {
        if (!vis[i]) {
            vector<int> cur;
            dfs(i, cur);
            cc.eb(cur);
        }
    }

    debug(cc);
    if (SZ(cc) == 2) {
        if (min(SZ(cc[0]), SZ(cc[1])) == 1) {
            bool rsv = false;
            if (SZ(cc[0]) < SZ(cc[1])) {
                swap(cc[0], cc[1]);
            }
            for (auto c1 : cc[0]) {
                for (auto c2 : cc[0]) {
                    if (rsv) {
                        break;
                    }
                    debug(c1, c2, edge[c1][c2]);
                    if (c1 != c2 && !edge[c1][c2]) {
                        rsv = true;
                        ans.eb(c1, c2);
                        ans.eb(c1, cc[1][0]);
                        ans.eb(c2, cc[1][0]);
                    }
                }
            }
            if (!rsv) {
                cout << -1 << endl;
                return 0;
            }
        } else {
            REP (i, 2) {
                REP (j, 2) {
                    ans.eb(cc[0][i], cc[1][j]);
                }
            }
        }
    } else if (SZ(cc) >= 3) {
        REP (i, SZ(cc)) {
            ans.eb(cc[i][0], cc[(i+1)%SZ(cc)][0]);
        }
    }

    cout << SZ(ans) << endl;
    for (auto p : ans) {
        if (p.X > p.Y) {
            swap(p.X, p.Y);
        }
        cout << p.X << " " << p.Y << endl;
    }
    return 0;
}
