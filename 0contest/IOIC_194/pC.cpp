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
const ll MAXN=1<<19;
const ll MAXLG=__lg(MAXN)+2;



ll anc[MAXLG][MAXN];
ll ddp[MAXN];
ll dep[MAXN];
vector<pii> edge[MAXN];
ll n,m;


void dfs(ll nd,ll par){
  anc[0][nd] = par;
  dep[nd] = dep[par] + 1;
  for(auto v:edge[nd]){
    if (v.X != par) {
        ddp[v.X] = ddp[nd] + v.Y;
        dfs(v.X,nd);
    }
  }
}
void build_lca(){
  for(ll i=1;i<MAXLG;i++){
    for(ll j=1;j<=n;j++){
      anc[i][j] = anc[i-1][anc[i-1][j]];
    }
  }
}

pair<ll,ll> query(ll u,ll v){
 
    ll ou = u,ov = v;
    if(dep[u] < dep[v])swap(u,v);
    for(ll i=MAXLG-1;i>=0;i--){
        if(dep[anc[i][u]] >= dep[v]) {
            u = anc[i][u];
        }
    }
    if(u==v)return {ddp[ov]+ddp[ou]-ddp[u]*2,u};

    for(ll i=MAXLG-1;i>=0;i--){
        if(anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    return {ddp[ov]+ddp[ou]-2*ddp[anc[0][u]],anc[0][u]};
}

ll get_half(ll nd,ll len) {
    ll hf = len >> 1;
    ll ptr = nd;
    for (ll i=MAXLG-1;i>=0;i--) {
        if (ddp[nd] - ddp[anc[i][ptr]] < hf) {
            ptr = anc[i][ptr];
        }
    }
    ll ret1 = ddp[nd] - ddp[ptr];
    ll ret2 = ddp[nd] - ddp[anc[0][ptr]];
   
    return min(max(ret1,len-ret1),max(ret2,len-ret2));
}


const ll MAXM = 1024;
ll cost[MAXM][MAXM];
ll pm[MAXM],pg[MAXM];


ll mx[MAXM],my[MAXM];
bool vy[MAXM],adj[MAXM][MAXM];

int greedy_matching()
{
    int c = 0;
    for (int x=0; x<m; ++x)
        if (mx[x] == -1)
            for (int y=0; y<m; ++y)
                if (my[y] == -1)
                    if (adj[x][y])
                    {
                        mx[x] = y; my[y] = x;
                        c++;
                        break;
                    }
    return c;
}
 
bool DFS(int x)
{
    for (int y=0; y<m; ++y)
        if (adj[x][y] && !vy[y])
        {
            vy[y] = true;
 
            if (my[y] == -1 || DFS(my[y]))
            {
                mx[x] = y; my[y] = x;
                return true;
            }
        }
    return false;
}

int bipartite_matching()
{
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
 
    int c = greedy_matching();
 
    for (int x=0; x<m; ++x)
        if (mx[x] == -1)  
        {
            memset(vy, false, sizeof(vy));
            if (DFS(x)) c++;
        }
    return c;
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n-1) {
        ll u,v,t;
        cin >> u >> v >> t;
        edge[u].emplace_back(v,t);
        edge[v].emplace_back(u,t);
    }

    REP (i,m) {
        cin >> pm[i];
    }
    REP (i,m) {
        cin >> pg[i];
    }
    debug("inped");
    dfs(1,1);
    build_lca();

    ll L = 0,R = 0;


    REP (i,m) {
        REP (j,m) {
            ll man = pm[i] ,wom = pg[j];
            pii ret = query(pm[i],pg[j]);
            ll dist = ret.X;
            ll aa = ret.Y;

            if (ddp[man] - ddp[aa] > ddp[wom] - ddp[aa]) {
                cost[i][j] = get_half(man,dist) * 2;
            } else {
                cost[i][j] = get_half(wom,dist) * 2;
            }
            R = max(cost[i][j],R);
        }
    }

    R += 10;
    while(L < R - 1) {
        ll mid = L + R >> 1;
        
        REP (i,m) {
            REP (j,m) {
                if (cost[i][j] <= mid) {
                    adj[i][j] = true;
                } else {
                    adj[i][j] = false;
                }
            }
        }


        if (bipartite_matching() == m){
            R = mid;
        } else {
            L = mid;
        }
    }

    cout << R << endl;
    return 0;
}


/*
10 4
1 2 9
1 3 4
3 5 8
3 6 7
6 7 6
1 4 2
4 8 6
8 9 1
8 10 7
1 2 3 4 5 6 7 8

*/