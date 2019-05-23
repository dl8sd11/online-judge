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
const ll MAXN = 500002;

namespace SEG {
    struct Node {
        ll l,r;
        Node *lc,*rc;
        ll data,tag;
        ll get() {
            return tag == -1 ? data : tag * (r-l);
        }
        void pull() {
            if (lc && rc) {
                data = lc->get() + rc->get();
            }
        }
        void push() {
            if ((lc && rc) && tag != -1) {
                data = tag * (r-l);
                lc->tag = tag;
                rc->tag = tag;
                tag = -1;
            }
        }
    };
    Node *root;

    Node *build(ll l,ll r) {
        if (r == l + 1) {
            return new Node{l,r,0,0,0,-1};
        }
        ll mid = (l + r) >> 1;
        return new Node{l,r,build(l,mid),build(mid,r),0,-1};
    }

    void chg(ll l,ll r,ll val,Node *nd) {
        if (l == nd->l && r == nd->r) {
            nd->tag = val;
        } else {
            ll mid = (nd->l + nd->r) >> 1;
            nd->push();
            if (l >= mid) {
                chg(l,r,val,nd->rc);
            } else if (r <= mid) {
                chg(l,r,val,nd->lc);
            } else {
                chg(l,mid,val,nd->lc);
                chg(mid,r,val,nd->rc);
            }
            nd->pull();
        }
    }

    ll query(ll l,ll r,Node *nd) {
        if (l == nd->l && r == nd->r) {
            return nd->get();
        } else {
            ll mid = (nd->l + nd->r) >> 1;
            nd->push();
            if (l >= mid) {
                return query(l,r,nd->rc);
            } else if (r <= mid) {
                return query(l,r,nd->lc);
            } else {
                return query(l,mid,nd->lc) + query(mid,r,nd->rc);
            }
        }
    }
}

ll n,q,sz[MAXN],son[MAXN],fat[MAXN],top[MAXN],in[MAXN],out[MAXN],ts;
vector<ll> edge[MAXN];

void dfs1 (ll nd,ll par) {
    sz[nd] = 1;
    son[nd] = 0;
    fat[nd] = par;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs1(v,nd);
            sz[nd] += sz[v];
            if (sz[v] > sz[son[nd]]) {
                son[nd] = v;
            }
        }
    }
}

void dfs2 (ll nd,ll tp) {
    in[nd] = ts++;
    top[nd] = tp;
    if (son[nd] != 0) {
        dfs2(son[nd],tp);
    }
    for (auto v : edge[nd]) {
        if (v != fat[nd] && v != son[nd]) {
            dfs2(v,v);
        }
    }
    out[nd] = ts;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs1(1,0);
    dfs2(1,1);
    SEG::root = SEG::build(0,n);
    cin >> q;
    while (q--) {
        ll c,v;
        cin >> c >> v;
        if (c == 1) {
            SEG::chg(in[v],out[v],1,SEG::root);
        } else if (c == 2) {
            while (v != 0) {
                SEG::chg(in[top[v]],in[v]+1,0,SEG::root);
                v = fat[top[v]];
            }
        } else {
            cout << SEG::query(in[v],in[v]+1,SEG::root) << endl;
        }
    }
    return 0;
}
