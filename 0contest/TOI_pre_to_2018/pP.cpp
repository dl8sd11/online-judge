#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
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
const int INF = 0x3f3f3f3f;
const ll MAXN = 1000003; 

int m,n,c,rc;
struct Edge {
    int t,w,nxt;
};
Edge G[MAXN];
Edge rG[MAXN];
int head[MAXN],rhead[MAXN];

int dis[MAXN];
bool vis[MAXN];
priority_queue<pii,vector<pii>,greater<pii> > pq;

ll dij(Edge *edge,int *hd) {
    while (SZ(pq)) {
        pq.pop();
    }
    MEM(vis,0);
    MEM(dis,INF);
    dis[1] = 0;
    pq.emplace(dis[1],1);

    REP (nu,n) {
        int fnd = -1;
        while (pq.size() && vis[fnd=pq.top().Y]) {
            pq.pop();
        }
        if (fnd == -1) {
            break;
        }
        vis[fnd] = true;
        for (int i=hd[fnd];i!=-1;i=edge[i].nxt) {
            pii e = {edge[i].t,edge[i].w};
            debug(fnd,e);
            if (dis[e.X] > dis[fnd] + e.Y) {
                dis[e.X] = dis[fnd] + e.Y;
                pq.emplace(dis[e.X],e.X);
            }
        }
    }
    pary(dis+1,dis+n+1);
    ll sum  = 0;
    REP1 (i,n) {
        if (dis[i] == INF) {
            return -1;
        }
        sum += dis[i];
    }
    return sum;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    MEM(head,-1);
    MEM(rhead,-1);
    REP (i,m) {
        int f,t,w;
        cin >> f >> t >> w;
        G[c] = {t,w,head[f]};
        head[f] = c++;
        rG[rc] = {f,w,rhead[t]};
        rhead[t] = rc++;
    }
    ll go = dij(G,head);
    ll bac = dij(rG,rhead);
    debug(go,bac);
    if (go == -1 || bac == -1) {
        assert(false);
        cout << 0 << endl;
    } else {
        cout << go + bac << endl;
    }
    return 0;
}
/* 海選加油 */
