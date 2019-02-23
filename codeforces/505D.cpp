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
const ll MAXN = 100003;

ll n,m,cc[MAXN],ccnt;
vector<ll> edge[MAXN],redge[MAXN];
bool vis[MAXN];
bool hsscc[MAXN];


vector<ll> topo;
void dfs1(ll nd) {
    vis[nd] = true;
    for (auto v : redge[nd]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    topo.emplace_back(nd);
}

ll ccs;
void dfs2(ll nd) {
    debug(nd);
    ccs++;
    vis[nd] = false;
    cc[nd] = ccnt;
    for (auto v : edge[nd]) {
        if (vis[v]) {
            dfs2(v);
        }
    }
}

ll ccsize[MAXN];
ll djs[MAXN],sz[MAXN],ans;
void init(ll a) {
    ans = a;
    REP1 (i,a) {
        djs[i] = i;
        sz[i] = 1;
    }
}

ll fnd(ll x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void uni(ll x,ll y) {
    if ((x=fnd(x)) == (y=fnd(y))) {
        return;
    }
    ans--;
    if (sz[x] > sz[y]) {
        swap(x,y);
    }
    djs[x] = y;
    sz[y] += sz[x];
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,m) {
        ll f,t;
        cin >> f >> t;
        edge[f].emplace_back(t);
        redge[t].emplace_back(f);
    }

    REP1 (i,n) {
        if (!vis[i]) {
            dfs1(i);
        }
    }
    debug(topo);
    for (auto it=topo.rbegin();it!=topo.rend();it++) {
        ll i = *it;
        if (vis[i]) {
            ccs = 0;
            dfs2(i);
            ccsize[ccnt++] = ccs;
        }
    }

    pary(cc+1,cc+n+1);

    init(n);
    REP1 (i,n) {
        for (auto v : edge[i]) {
            uni(i,v);
        }
    }
    
    REP1 (i,n) {
        hsscc[fnd(i)] |= ccsize[cc[i]] > 1;
    }

    ans = n - ans;
    REP1 (i,n) {
        if (hsscc[i]) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}
/*
6 7
1 2
2 3
3 1
3 4
4 5
5 6
6 4
*/