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
// const ll MAXN =

const int maxn = 2e5+5;
#define MAXN maxn
#define f first
#define s second
int pa[maxn];
int sz[maxn];
int v[maxn];
int find(int x){return pa[x] == x?x:pa[x] = find(pa[x]);}

int ans = 0;
vector<pii> g[maxn];
int n,m, asn[maxn];

void bf (int idx) {
    if (idx == m) {
        bool flag = true;
        for (int i=0; i<n; ++i) {
            int sum = 0;
            for (auto v : g[i]) {
                sum += asn[v.f];
            }
            flag &= (sum % 5 == 0);
        }
        ans += flag;
    } else {
        for (int i=0; i<5; i++) {
            asn[idx] = i;
            bf(idx+1);
        }
    }

}

vector <int> tree[MAXN*2];

int low[MAXN], dfn[MAXN], dfs_clock = 0;
vector<vector<int> > bcc;
vector<vector<pii> > ebcc;
bool is_cut[MAXN];

vector<int> stk;
vector<pii> edg;
void dfs_bcc (int nd, int pa) {
    low[nd] = dfn[nd] = dfs_clock++;
    stk.eb(nd);
    debug(nd, pa);
    for (auto e : g[nd]) {
        int v = e.f;
        if (v != pa) {
            edg.eb(v, nd);
            if (dfn[v] == -1) { // tree edge
                dfs_bcc(nd, v);
                low[nd] = min(low[nd], low[v]);
                if (low[v] >= dfn[nd]) {
                    debug(nd, pa, v, low[v], dfn[nd]);
                    is_cut[nd] |= (dfn[nd] > 0 || dfn[v] > 1); // not root or > 1 child
                    vector<int> new_comp = {nd};
                    while (new_comp.back() != v) {
                        new_comp.eb(stk.back());
                        stk.pop_back();
                    }

                    vector<pii> new_ecomp;

                    
                    bcc.eb(new_comp);
                }
            } else { // back edge
                low[nd] = min(low[nd], dfn[v]);
            }


        }
    }
}


int main () {
    TIME(main);
    IOS();
    int t; cin>>t;
    while (t--) {
         cin>>n>>m;
        for (int i = 0; i<n; ++i) {
            pa[i] = i, v[i] = 0, sz[i] = 1;
            g[i].clear();
        }
        for (int i = 0; i<m; ++i) {
            int a,b; cin>>a>>b; 
            --a;--b;
            g[a].eb(i);
            g[b].eb(i);
            if (find(a) == find(b)) {
                v[find(a)] ++;
            }else{
                v[find(a)] += v[find(b)];
                v[find(a)]++;
                sz[find(a)] += sz[find(b)];
                pa[find(b)] = find(a);
            }
        }
        int mo = 0;
        for (int i = 0; i<n; ++i) {

            if (find(i) == i) {
                int pi = find(i);
                if (sz[pi] == v[pi] && sz[pi] % 2 == 0) {
                    mo++;
                } else {
                    mo += max(v[pi]-sz[pi],0);
                }

            }
        }
        ll re= 1; while(mo--) re = re * 5 % 998244353;

#ifdef tmd
        ans = 0;
        bf(0);
        debug(ans, re);
#endif
        cout<<re<<endl;
    }

    return 0;
}
