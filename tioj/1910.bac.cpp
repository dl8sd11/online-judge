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


ll t,n,m,q;
vector<pii> edge[MAXN];

class SEG {
public:
    ll org[MAXN];

    struct node {
        ll l,r;
        node *lc,*rc;
        ll data,tag;
    };
    node *root;
    node *build (ll l,ll r) {
        if (l == r-1) {
            return new node {l,r,0,0,org[l],0};
        }
        ll mid = l+r>>1;
        node *ret = new node{l,r,build(l,mid),build(mid,r),0,0};
        ret->data = max(ret->lc->data,ret->rc->data);
        return ret;
    }

    void build_seg() {
        root = build(0,n);
    }

    void add(ll l,ll r,node *nd,ll data) {
        if (l == nd->l && r == nd->r) {
            nd->tag += data;
        } else {
            ll mid = nd->l+nd->r>>1;
            if (l >= mid) {
                add(l,r,nd->rc,data);
            } else if (r <= mid) {
                add(l,r,nd->lc,data);
            } else {
                add(l,mid,nd->lc,data);
                add(mid,r,nd->rc,data);
            }
            nd->data = max(nd->lc->data+nd->lc->tag,nd->rc->data+nd->rc->tag);
        }
    }

    ll query(ll l,ll r,node *nd) {
        if (l == nd->l && r == nd->r) {
            return nd->data + nd->tag;
        } else {
            ll mid = nd->l+nd->r>>1;
            if (l >= mid) {
                return query(l,r,nd->rc) + nd->tag;
            } else if (r <= mid) {
                return query(l,r,nd->lc) + nd->tag;
            } else {
                return max(query(l,mid,nd->lc),query(mid,r,nd->rc)) + nd->tag;
            }
        }
    }
    /*
6
5 1 2 3 4 7
0 0 6
1 1 3 10
0 0 6
1 2 4 10
0 0 6

    */
};
namespace BCC{
    ll timestamp;
    ll low[MAXN],dfn[MAXN];
    vector<ll> stk;
    vector<vector<ll> > cc;
    ll comp[MAXN];

    void DFS (ll nd,ll par) {
        low[nd] = dfn[nd] = ++timestamp;
        stk.eb(nd);
        for (auto v:edge[nd]) {
            if (!dfn[v.X]) { 
                /* tree edge */
                DFS(v.X ,nd);
            }

            if (v.X != par) {
                /* not to parent */
                low[nd] = min(low[nd],low[v.X]);
            }
        }

        if (dfn[nd] == low[nd]) {
            vector<ll> new_cc;
            while (true) {
                ll cur = stk.back();stk.pop_back();
                comp[cur] = SZ(cc);
                new_cc.eb(cur);
                if (cur == nd) {
                    break;
                }
            }
            cc.eb(new_cc);
        }
    }

    void build () {
        timestamp = 0;
        MEM(dfn,0);
        DFS(0,0);
    }
}

namespace CC {
    ll dis[MAXN];
    pii lst[MAXN];
    bool vis[MAXN];
    vector<pii> G[MAXN];

    /* LCA */
    ll anc[MAXN][MAXLG];
    ll dp[MAXN][MAXLG];
    ll dep[MAXN];
    /* END LCA */

    void DFS(ll nd,ll par) {
        dep[nd] = dep[par] + 1;
        anc[nd][0] = par;
        for (auto v:G[nd]) if (v.X != par) {
            DFS(v.X,nd);
            dp[v.X][0] = v.Y;
        }
    }

    void prim (ll root) {    
        priority_queue<pii,vector<pii>,greater<pii> > pq;
        pq.emplace(0,root);
        dis[root] = 0;
        while (pq.size()) {
            ll cur = pq.top().Y;pq.pop();
            if (vis[cur]) {
                continue;
            }
            vis[cur] = true;
            
            if (cur != root) {
                G[cur].eb(lst[cur]);
                G[lst[cur].X].eb(cur,lst[cur].Y);
            }
            for (auto v:edge[cur]) {
                if (vis[v.X] || BCC::comp[v.X] != BCC::comp[cur]) {
                    continue;
                }
                if (dis[v.X] > v.Y) {
                    dis[v.X] = v.Y;
                    lst[v.X] = {cur,v.Y};
                    pq.emplace(v.Y,v.X);
                }
            }
        }
    }

    void build_lca () {
        REP1 (i,MAXLG-1) {
            REP (j,n) {
                anc[j][i] = anc[anc[j][i-1]][i-1];
                dp[j][i] = max(dp[j][i-1],dp[anc[j][i-1]][i-1]);
            }
        }
    }

    ll dist (ll u,ll v) {
        if (u == v) {
            return 0;
        }
        if (dep[u] > dep[v]) {
            swap(u,v);
        }

        ll ret = 0;
        for (ll i=MAXLG-1;i>=0;i--) {
            if (dep[anc[v][i]] >= dep[u]) {
                ret = max(ret,dp[v][i]);
                v = anc[v][i];
            }
        }

        if (v == u) {
            return ret;
        }

        for (ll i=MAXLG-1;i>=0;i--) {
            if (anc[v][i] != anc[u][i]) {
                ret = max(ret,dp[v][i]);
                ret = max(ret,dp[u][i]);
                v = anc[v][i];
                u = anc[u][i];
            }
        }
        ret = max(ret,dp[u][0]);
        ret = max(ret,dp[v][0]);
        return ret;
    }
    void build () {
        MEM(dis,INF);
        MEM(vis,0);
        debug(BCC::cc);
        REP (i,SZ(BCC::cc)) {
            prim(BCC::cc[i].front());
            DFS(BCC::cc[i].front(),BCC::cc[i].front());
        }
        build_lca();
    }
}


/********** Good Luck :) **********/
int main()
{
    IOS();

    
    SEG seg1;
    cin >> n;
    REP (i,n) {
        cin >>seg1.org[i];
    }
    seg1.build_seg();

    ll cmd;
    while (cin >> cmd) {
        ll l,r;
        cin >> l >> r;
        if (cmd == 0) {
            cout << seg1.query(l,r,seg1.root) << endl;
        } else {
            ll data;
            cin >> data;
            seg1.add(l,r,seg1.root,data);
        }
    }
    // cin >> t >> n >> m >> q;
    // REP (i,m) {
    //     ll u,v,w;
    //     cin >> u >> v >> w;
    //     edge[u].eb(v,w);
    //     edge[v].eb(u,w);
    // }

    // BCC::build();
    // CC::build();
    return 0;
}

/*
21:09 planned
21:34 BCC tested
21:57 break
22:27 continue LCA
22:58 LCA built break
8:20 Start seg
9:27 seg tested breakw

pre:
    0. BCC
    1. MST
    2. LCA in MST
    3. HL Dec
    4. Segment tree RR

0:
    0. Bridge HL +k
    1. CC HL +k
1:
    0. Bridge RMQ
    1. (s,t) CC RMQ
    2. s,t MST LCA
*/


/*
1
14 17 0
0 1 0
0 3 0
1 2 0
2 3 1
3 5 0
3 4 1
4 6 0
5 6 0
5 10 0
10 7 0
7 8 0
10 8 0
8 9 0
10 11 0
11 12 0
11 13 0
12 13 0
*/

/*
One CC
1
12 19 0
0 1 7
0 2 6
0 3 2
1 4 1
1 5 2
2 6 2
2 7 3
5 8 4
5 9 0
5 10 3
10 11 5
6 10 9
2 5 8
4 0 10
8 0 9
9 0 8
11 0 13
7 0 9
3 7 11
*/