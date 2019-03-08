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
const ll MAXN = 1003;

ll n,m,q;
vector<ll> edge[MAXN];

ll djs[MAXN],sz[MAXN];

bool is_bridge[MAXN][MAXN];
ll dfn[MAXN],low[MAXN],ts,cc[MAXN],ccnt;
void bridge(ll nd,ll par,ll c) {
    cc[nd] = c;
    dfn[nd] = low[nd] = ++ts;
    for (auto e : edge[nd]) {
        if (dfn[e] == 0) {
            bridge(e,nd,c);
        }
        if (e != par) {
            low[nd] = min(low[nd],low[e]);
        }
    }
    if (low[nd] > dfn[par]) {
        is_bridge[nd][par] = true;
        is_bridge[par][nd] = true;
    }
}

bool dfs(ll nd,ll par,ll g) {
    if (nd == g) {
        return true;
    }
    bool ret = false;
    for (auto e : edge[nd]) {
        if (is_bridge[e][nd] && e != par) {
            ret |= dfs(e,nd,g);
        }
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m >> q;
    REP (i,m) {
        ll u,v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    REP1 (i,n) {
        if (cc[i] == 0) {
            bridge(i,i,++ccnt);
        }
    }

    pary(cc+1,cc+n+1);

    REP1 (i,n) {
        REP1 (j,i-1) {
            if (is_bridge[i][j]) {
                debug(i,j);
            }
        }
    }
    REP (i,q) {
        ll x,y;
        cin >> x >> y;
        if (cc[x] == cc[y]) {
            cout << dfs(x,x,y) << endl;
        } else {
            cout << 0 << endl;
        }
    }

    return 0;
}
