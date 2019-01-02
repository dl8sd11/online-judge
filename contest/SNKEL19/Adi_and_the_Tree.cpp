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
const ll MAXN=3e5+5;
const ll MAXLG=__lg(MAXN)+2;

namespace seg{

    struct node {
        ll l,r;
        node *lc,*rc;
        ll data;
        bool rev;
        void push() {
            if (rev) {
                data = (r-l) - data;
                rev = 0;
                if (lc) {
                    lc->rev ^= 1;
                }
                if (rc) {
                    rc->rev ^= 1;
                }
            }
        }

        void pull() {
            if (lc) {
                lc->push();
            }
            if (rc) {
                rc->push();
            }
            data = lc->data + rc->data;
        }
    };

    node *build(ll l,ll r) {
        if (r == l+1) return new node({l,r,0,0,0,0});
        ll mid = (l+r)>>1;
        return new node({l,r,build(l,mid),build(mid,r),0,0});
    }

    ll query(ll l,ll r,node *nd) {
        nd->push();
        if (nd->l == l && nd->r ==  r) {
            return nd->data;
        }
        ll mid = (nd->l+nd->r)>>1;
        if (l >= mid) {
            return query(l,r,nd->rc);
        } else if (r <= mid) {
            return query(l,r,nd->lc);
        } else {
            return query(l,mid,nd->lc) + query(mid,r,nd->rc);
        }
    }

    void modi(ll l,ll r,node *nd) {
        nd->push();
        if (nd->l == l && nd->r == r) {
            nd->rev ^= 1;
            return;
        }
        ll mid = (nd->l+nd->r)>>1;
        if (l >= mid) {
            modi(l,r,nd->rc);
        } else if (r <= mid) {
            modi(l,r,nd->lc);
        } else {
            modi(l,mid,nd->lc);
            modi(mid,r,nd->rc);
        }
        nd->pull();
    }
};
seg::node *root;

namespace tree {
    vector<ll> edge[MAXN];
    ll dep[MAXN],sz[MAXN],fat[MAXN],son[MAXN],top[MAXN],in[MAXN];
    ll vert;
    void DFS1(ll nd,ll par) {
        dep[nd] = dep[par] + 1;
        sz[nd] = 1;
        fat[nd] = par;
        son[nd] = 0;
        for (auto v:edge[nd]) {
            if (v == par) continue;
            DFS1(v,nd);
            sz[nd] += sz[v];
            if (sz[v] > sz[son[nd]]) son[nd] = v;
        }
    }

    void DFS2(ll nd,ll tp) {
        in[nd] = vert++;
        top[nd] = tp;
        if (son[nd]) DFS2(son[nd],tp);
        for (auto v:edge[nd]) {
            if (v == fat[nd] || v == son[nd]) continue;
            DFS2(v,v);
        }
    }

    void flip(ll x,ll y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x,y);
            seg::modi(in[top[x]],in[x]+1,root);
            x = fat[top[x]];
        }
        if (x != y) {
            if (dep[x] < dep[y]) swap(x,y);
            seg::modi(in[son[y]],in[x]+1,root);
        }
    }
};

ll n,q;
/********** Good Luck :) **********/
int main()
{
    IOS();
    root = seg::build(0,MAXN);
    
    cin >> n;
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        tree::edge[u].eb(v);
        tree::edge[v].eb(u);
    }

    tree::DFS1(1,1);
    tree::DFS2(1,1);

    cin >> q;
    while (q--) {
        ll u,v;
        cin >> u >> v;
        tree::flip(u,v);
        cout << seg::query(0,MAXN,root) << endl;
    }
    return 0;
}
