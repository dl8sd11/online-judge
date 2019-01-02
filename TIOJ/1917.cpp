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
const ll MAXN=1500;
const ll MAXLG=__lg(MAXN)+2;


ll T,n,L,U,k;
bool ban[MAXN][MAXN];
ll x[MAXN],y[MAXN];


struct Edge{
    ll t,cap,flow,cost,nxt;
};
vector<Edge> edge;
ll head[MAXN*2];
void add_edge (ll f,ll t,ll cap,ll cost) {
    edge.pb({t,cap,0,cost,head[f]});
    head[f] = SZ(edge) - 1;
    edge.pb({f,0,0,-cost,head[t]});
    head[t] = SZ(edge) - 1;
}

ll dis[MAXN*2],nv[MAXN*2],ne[MAXN],cnt[MAXN*2];
ll MCMF (ll s,ll t) {
    ll flow = 0;
    ll cost = 0;
    while (true) {
        MEM(dis,INF);
        MEM(cnt,0);
        MEM(nv,-1);
        queue<ll> BFS;
        BFS.emplace(s);
        dis[s] = 0;
        while (BFS.size()) {
            ll cur = BFS.front();BFS.pop();
            cnt[cur]++;
            if (cnt[cur] >= n*2 + 13) {
                break;
            }
            for (ll i=head[cur];i!=-1;i=edge[i].nxt) {
                ll xp = edge[i].t;
                if (edge[i].cap > edge[i].flow && dis[xp] > dis[cur] + edge[i].cost) {
                    dis[xp] = dis[cur] + edge[i].cost;
                    nv[xp] = cur;
                    ne[xp] = i;
                    BFS.emplace(xp);
                }
            }
        }
        if (dis[t] == INF) {
            break;
        }

        ll ct = 0;
        ll lim = INF,nd = t;
        while (nd != s) {
            lim = min(lim,edge[ne[nd]].cap-edge[ne[nd]].flow);
            ct += edge[ne[nd]].cost;
            nd = nv[nd];
        }

        nd = t;
        while (nd != s) {
            edge[ne[nd]].flow += lim;
            edge[ne[nd]^1].flow -= lim;
            nd = nv[nd];
        }
        flow += lim;


        debug(lim,ct);
        cost += lim * ct;
    }
    debug(flow);
    if (flow == n) {
        return cost;
    } else {
        return -1;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> T;
    while (T--) {
        MEM(head,-1);
        MEM(ban,0);
        edge.clear();
        cin >> n >> L >> U >> k;
        REP (i,k) {
            ll u,v;
            cin >> u >> v; // banned
            ban[u][v] = 1;
            ban[u][v] = 1;
        }

        REP1 (i,n) {
            cin >> x[i];
        }

        REP1 (i,n) {
            cin >> y[i];
        }

        /*
            vertex distrubute
            0 : source
            1~n: x - point
            n+1~2n: y - point
            2n+1: sink
        */

        REP1 (i,n) {
            add_edge(0,i,1,0);
        }

        REP1 (i,n) {
            REP1 (j,n) {
                if (!ban[i][j]) {
                    if (x[i] + y[j] < L) {
                        add_edge(i,j+n,1,0);
                    } else if (x[i] + y[j] < U) {
                        add_edge(i,j+n,1,x[i]+y[j]-L);
                    } else {
                        add_edge(i,j+n,1,U-L);
                    }
                }
            }
        }

        REP1 (i,n) {
            add_edge(n+i,n*2+1,1,0);
        }
        ll ans = MCMF(0,2*n+1);
        if (ans == -1) {
            cout << "no" << endl;
        } else {
            cout << ans << endl;
        }

    }
    return 0;
}
