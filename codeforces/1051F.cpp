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
const ll MAXN = 100050;
const ll MAXLG = __lg(MAXN) + 3;
ll n,m;
vector<pii> edge[MAXN];
vector<ll> node;
map<ll,ll> nid;

ll dep[MAXN],dis[MAXN],anc[MAXLG][MAXN];
bool vis[MAXN];
void dfs(ll nd, ll par) {
    vis[nd] = true;
    dep[nd] = dep[par] + 1;
    anc[0][nd] = par;
    for (auto v : edge[nd]) {
        if (v.X != par) {
            if (!vis[v.X]) {
                dis[v.X] = dis[nd] + v.Y;
                dfs(v.X,nd);
            } else {
                node.emplace_back(v.X);
                node.emplace_back(nd);
            }
        }
    }
}

void build_lca() {
    REP1 (i,MAXLG-1) {
        REP1 (j,n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

ll dist(ll u,ll v) {
    if (u == v) {
        return 0;
    }
    if (dep[u] > dep[v]) {
        swap(u,v);
    }
    ll ret = 0;
    for (ll i=MAXLG-1;i>=0;i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            ret += dis[v] - dis[anc[i][v]];
            v = anc[i][v];
        }
    }

    if (u == v) {
        return ret;
    }

    for (ll i=MAXLG-1;i>=0;i--) {
        if (anc[i][u] != anc[i][v]) {
            ret += dis[u] - dis[anc[i][u]];
            ret += dis[v] - dis[anc[i][v]];
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    ret += dis[u] - dis[anc[0][u]];
    ret += dis[v] - dis[anc[0][v]];

    return ret;
}

ll trans[50][MAXN];
bool dvis[MAXN];
void dijkstra(ll src) {
    priority_queue<pii,vector<pii>,greater<pii> > pq;
    pq.emplace(0,src);
    ll sid = nid[src];
    trans[sid][src] = 0;
    MEM(dvis,0);

    REP (i,n) {
        ll fnd = -1;
        while (pq.size() && dvis[fnd=pq.top().Y]) {
            pq.pop();
        }
        assert(fnd != -1);
        dvis[fnd] = true;

        for (auto p : edge[fnd]) {
            if (trans[sid][p.X] > trans[sid][fnd] + p.Y) {
                trans[sid][p.X] = trans[sid][fnd] + p.Y;
                pq.emplace(trans[sid][p.X],p.X);
            }
        }
    }
}

ll dp[50][50];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,m) {
        ll u,v,w;
        cin >> u >> v >> w;
        edge[u].emplace_back(v,w);
        edge[v].emplace_back(u,w);
    }

    dfs(1,1);
    build_lca();

    sort(ALL(node));
    node.resize(unique(ALL(node))-node.begin());
    debug(node);
    MEM(trans,INF);


    REP (i,SZ(node)) {
        nid[node[i]] = i;
        dijkstra(node[i]);
    }

    // REP (i,SZ(node)) {
    //     REP (j,SZ(node)) {
    //         dp[i][j] = dp[j][i] = dist(node[i],node[j]);
    //     }
    // }

    // REP (i,SZ(node)) {
    //     for (auto v : edge[node[i]]) {
    //         if (nid.find(v.X) != nid.end()) {
    //         debug(i,nid[v.X],v.Y);
    //             dp[i][nid[v.X]] = min(dp[i][nid[v.X]],v.Y);
    //         }
    //     }
    // }

    // REP (k,SZ(node)) {
    //     REP (i,SZ(node)) {
    //         REP (j,SZ(node)) {
    //             dp[i][j] = min(dp[i][j],dp[i][k]+dp[k][j]);
    //         }
    //     }
    // }

    #ifdef tmd

    REP (i,SZ(node)) {
        REP (j,SZ(node)) {
            cout << dp[i][j] <<" ";
        }
        cout << endl;
    }
    #endif

    ll q;
    cin >> q;
    while (q--) {
        ll u,v;
        cin >> u >> v;
        ll ret = dist(u,v);

        REP (i,SZ(node)) {
            REP (j,SZ(node)) {
                ret = min(ret,trans[i][u]+trans[j][v]+trans[i][node[j]]);
            }
        }

        cout << ret << endl;
    }

    return 0;
}
