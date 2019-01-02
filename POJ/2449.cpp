#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cmath>
#include<queue>
#include<stack>
using namespace std;
typedef int ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define MEM(i,n) memset(i,n,sizeof i)
#define X first
#define Y second
#define SZ(_a) (int)_a.size()
#define ALL(_a) _a.begin(),_a.end()
#define pb push_back
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
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif


const ll MAXN=1e5+5,MAXlg=__lg(MAXN)+2;
const ll MOD=1000000007;
const ll INF=0x3f3f3f3f;

struct Edge {
    ll t,w,next;
} edge[200003];

ll n,m;
ll head[2][1024],ioi;
void add_edge(ll f,ll t,ll w,ll r) {
    edge[ioi].t = t;
    edge[ioi].w = w;
    edge[ioi].next = head[r][f];
    head[r][f] = ioi++;
}

bool vis[MAXN];
ll dis[MAXN];
void Dijkstra(ll s) {
    priority_queue<pii,vector<pii>,greater<pii> > pq;
    MEM(dis,INF);
    pq.push({0,s});
    dis[s] = 0;

    REP (un,n) {
        ll found = -1;
        while (pq.size() && vis[found = pq.top().Y]) pq.pop();
        if (found == -1) {
            break;
        }
        vis[found] = true;
        for (ll i=head[1][found];i!=-1;i=edge[i].next) {
            ll cur = edge[i].t;
            if (dis[cur] > dis[found] + edge[i].w) {
                dis[cur] = dis[found] + edge[i].w;
                pq.push({dis[cur],cur});
            }
        }
    }
}


struct cp {
    ll g,h,v;
    bool operator < (const cp cp2) const{
        return g + h > cp2.g + cp2.h;
    }
};
ll AStar(ll s,ll t,ll k) {
    // return the kth path length
    if (s==t) k++;
    
    priority_queue<cp> pq;
    pq.push({0,dis[s],s});
    ll cnt = 0;
    while (pq.size()) {
        cp cur = pq.top();pq.pop();
        debug(cur.v);
        if (cur.v == t) {
            if (++cnt == k) {
                return cur.g + cur.h;
            }
            debug(cnt,cur.g + cur.h);
        }

        for (ll i=head[0][cur.v];i!=-1;i=edge[i].next) {
            pq.push({cur.g + edge[i].w,dis[edge[i].t],edge[i].t});
        }
    }

    return -1;
}
int main()
{
    IOS();
    scanf("%d%d",&n,&m);

    MEM(head,-1);
    REP (i,m) {
        ll f,t,w;
        scanf("%d%d%d",&f,&t,&w);
        add_edge(f,t,w,0);
        add_edge(t,f,w,1);
    }

    ll s,t,k;
    scanf("%d%d%d",&s,&t,&k);

    Dijkstra(t);
    pary(dis+1,dis+n+1);

    cout << AStar(s,t,k) << endl;
    return 0;
}
