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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;


ll anc[MAXLG][MAXN];
ll dep[MAXN],fat[MAXN];
vector<pii> edge[MAXN];
ll n,q,a,b;


void dfs(ll nd,ll par){
  anc[0][nd] = par;
  dep[nd] = dep[par] + 1;
  for(auto v:edge[nd]){
    if(v.X!=par) dfs(v.X,nd);
    fat[v.X] = v.Y; 
  }
}
void build_lca(){
  for(ll i=1;i<MAXLG;i++){
    for(ll j=1;j<=n;j++){
      anc[i][j] = anc[i-1][anc[i-1][j]];
    }
  }
}

ll query(ll u,ll v){
  if(dep[u] < dep[v])swap(u,v);
  for(ll i=MAXLG-1;i>=0;i--){
    if(dep[anc[i][u]] >= dep[v]) u = anc[i][u];
  }
  if(u==v)return u;

  for(ll i=MAXLG-1;i>=0;i--){
    if(anc[i][u] != anc[i][v]) {
      u = anc[i][u];
      v = anc[i][v];
    }
  }

  return anc[0][u];
}

ll kthanc(ll nd,ll k) {
    ll tmp = nd;
    for (ll i=MAXLG-1;i>=0;i--) {
        if (dep[nd] - dep[anc[i][tmp]] <= k) {
            tmp = anc[i][tmp];
        }
    }
    return tmp;
}

ll dp1[MAXN],dp2[MAXN];
void dfs2(ll nd,ll par) {
    if (nd != par) {
        if (fat[nd] >= fat[par] || par == 1) {
            dp1[nd] = dp1[par] + 1;
        } else {
            dp1[nd] = 1;
        }
        if (fat[nd] <= fat[par] || par == 1) {
            dp2[nd] = dp2[par] + 1;
        } else {
            dp2[nd] = 1;
        }
    }
    for (auto e : edge[nd]) {
        if (e.X != par) {
            dfs2(e.X,nd);
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;
    REP (i,n-1) {
        ll u,v,d;
        cin >> u >> v >> d;
        edge[u].emplace_back(v,d);
        edge[v].emplace_back(u,d);
    }

    dfs(1,1);
    build_lca();
    dfs2(1,1);

    pary(dp1+1,dp1+n+1);
    pary(dp2+1,dp2+n+1);
    while (q--) {
        cin >> a >> b;
        ll l = query(a,b);
        debug(l);
        debug(kthanc(a,dep[a]-dep[l]-1),kthanc(b,dep[b]-dep[l]-1));
        if (dp1[a] >= dep[a]-dep[l] && dp2[b] >= dep[b] - dep[l] && (a == l || b == l || fat[kthanc(a,dep[a]-dep[l]-1)] >= fat[kthanc(b,dep[b]-dep[l]-1)])) {
            cout << "YES" << endl;
        } else if (dp2[a] >= dep[a]-dep[l] && dp1[b] >= dep[b] - dep[l] && (a == l || b == l || fat[kthanc(a,dep[a]-dep[l]-1)] <= fat[kthanc(b,dep[b]-dep[l]-1)])) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
