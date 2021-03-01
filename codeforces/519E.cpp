#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
const ll MAXN = 100002;
const ll MAXLG = __lg(MAXN)+3;

int n,q,dep[MAXN],anc[MAXN][MAXLG],sz[MAXN];
vector<int> edge[MAXN];

void dfs(int nd,int par) {
    dep[nd] = dep[par] + 1;
    anc[nd][0] = par;
    sz[nd] = 1;
    for (int v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
            sz[nd] += sz[v];
        }
    }
}
void build() {
    dfs(1,1);
    for (int i=1;i<MAXLG;i++) {
        for (int j=1;j<=n;j++) {
            anc[j][i] = anc[anc[j][i-1]][i-1];
        }
    }
}

int kth(int nd,int dis) {
    for (int i=MAXLG-1;i>=0;i--) {
        if ((dis>>i)&1) {
            nd = anc[nd][i];
        } 
    }
    return nd;
}

int query(int u,int v) {
    if (u == v) {
        return sz[1];
    }
    int ou = u,ov = v;
    if (dep[u] < dep[v]) {
        swap(u,v);
    }
    for (int i=MAXLG-1;i>=0;i--) {
        if (dep[anc[u][i]] >= dep[v]) {
            u = anc[u][i];
        }
    }
    for (int i=MAXLG-1;i>=0;i--) {
        if (anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }
    }
    int lca = u == v ? u : anc[u][0];
    debug(lca);
    u = ou,v = ov;
    int dis = dep[u] + dep[v] - dep[lca]*2;
    
    if (dis & 1) {
        return 0;
    } else {
        if (dep[u] == dep[v]) {
            return sz[1] - sz[kth(u,dis/2-1)] - sz[kth(v,dis/2-1)];
        } else {
            if (dep[u] > dep[v]) {
                return sz[kth(u,dis/2)] - sz[kth(u,dis/2-1)];
            } else {
                return sz[kth(v,dis/2)] - sz[kth(v,dis/2-1)];
            }
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n-1) {
        int u,v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    build();
    cin >> q;

    while (q--) {
        int u,v;
        cin >> u >> v;
        cout << query(u,v) << endl;
    }
    return 0;
}
