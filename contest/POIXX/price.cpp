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
const ll MAXN=700+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,m,k,a,b;
vector<pii> edge[MAXN];
vector<pii> nedge;

bool vis[MAXN];
ll dis[MAXN][MAXN],ddis[MAXN];
void DFS(ll nd,ll par,ll lev,ll anc) {
    dis[nd][anc] = min(lev,dis[nd][anc]);
    if (lev == 2) {
        return;
    }
    for (auto p:edge[nd]) if (par != p.X) {
        DFS(p.X,nd,lev+1,anc);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m >> k >> a >> b;
    REP (i,m) {
        ll u,v;
        cin >> u >> v;
        edge[u].eb(v,a);
        edge[v].eb(u,a);
    }

    MEM(dis,INF);

    REP1 (i,n) {
        DFS(i,i,0,i);
    }

    REP1 (i,n) {
        REP1 (j,i) {
            debug(dis[i][j]);
            if (dis[i][j] == 2) {
                edge[i].eb(j,b);
                edge[j].eb(i,b);
            }
        }
    }

    pary(edge+1,edge+n+1);

    MEM(ddis,INF);
    MEM(vis,0);

    priority_queue<pii,vector<pii>,greater<pii> > pq;
    pq.emplace(0,k);
    ddis[k] = 0;

    REP (i,n) {
        ll found = -1;
        while (pq.size() && vis[found=pq.top().Y]) pq.pop();
        if (found == -1) break;

        vis[found] = true;
        for (auto p:edge[found]) {
            if (ddis[p.X] > ddis[found] + p.Y) {
                ddis[p.X] = ddis[found] + p.Y;
                pq.emplace(ddis[p.X],p.X);
            }
        }
    }

    REP1 (i,n) {
        cout << ddis[i] << endl;
    }
    return 0;
}
