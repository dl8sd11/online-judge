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
const ll MAXN = 100005;
const ll MAXLG = __lg(100005) + 5;

ll n,m,dep[MAXN],anc[MAXN][MAXLG];
pii h[MAXN];
vector<ll> edge[MAXN];

ll cross(ll a,ll b,ll o) {
    pii oa = {h[a].X-h[o].X,h[a].Y-h[o].Y};
    pii ob = {h[b].X-h[o].X,h[b].Y-h[o].Y};
    return oa.X*ob.Y - oa.Y*ob.X;
}

void build_edge (ll s,ll p) {
    anc[s][0] = p;
    edge[s].eb(p);
    edge[p].eb(s);
}

void dfs(ll nd,ll par) {
    dep[nd] = dep[par] + 1;
    assert(anc[nd][0] == par);

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
        }
    }
}

void build_lca() {
    REP1 (i,MAXLG-1) {
        REP1 (j,n) {
            anc[j][i] = anc[anc[j][i-1]][i-1];
        }
    }
}

ll lca(ll x,ll y) {
    if (dep[x] < dep[y]) {
        swap(x,y);
    }
    for (ll i=MAXLG-1; i>=0; i--) {
        if (dep[anc[x][i]] >= dep[y]) {
            x = anc[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (ll i=MAXLG-1; i>=0; i--) {
        if (anc[x][i] != anc[y][i]) {
            x = anc[x][i];
            y = anc[y][i];
        }
    }
    return anc[x][0];
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP1 (i,n) {
        cin >> h[i].X >> h[i].Y;
    }

    vector<ll> stk;
    stk.eb(n);
    anc[n][0] = n;
    for (ll i=n-1;i>=1;i--) {
        bool sm = false;
        ll lst = -1;
        while (SZ(stk) > 1) {
            if (cross(i,stk[SZ(stk)-2],stk.back()) == 0) {
                if (!sm) {
                    lst = stk.back();
                    sm = true;
                }
                stk.pop_back();
            } else if (cross(i,stk[SZ(stk)-2],stk.back()) < 0) {
                stk.pop_back();
            } else {
                break;
            }
        }
        if (sm) {
            build_edge(i,lst);
        } else {
            build_edge(i,stk.back());
        }
        stk.eb(i);
    }

    dfs(n,n);
    build_lca();

    cin >> m;
    REP (i,m) {
        ll a,b;
        cin >> a >> b;
        cout << lca(a,b) << " \n"[i==m-1];
    }
    return 0;
}
