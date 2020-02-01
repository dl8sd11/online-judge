#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
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
const ll MAXN=1e6+5;
const ll MAXLG=__lg(MAXN)+2;

stack<pair<ll*,ll> > stk_sz;
stack<pair<ll*,ll> > stk_djs;

ll djs[MAXN],sz[MAXN],ans;

void init(ll n) {
    while (stk_sz.size()) {
        stk_sz.pop();
    }
    while (stk_djs.size()) {
        stk_djs.pop();
    }
    ans = n;
    REP (i,n) {
        djs[i] = i;
        sz[i] = 1;
    }
}
ll fnd(ll x) {
    while (x != djs[x]) {
        x = djs[x];
    }
    return x;
}

bool uni(ll x,ll y) {
    x = fnd(x);
    y = fnd(y);
    if (x == y) {
        return 0;
    }
    if (sz[x] > sz[y]) {
        swap(x,y);
    }
    stk_sz.emplace(&sz[y],sz[y]);
    stk_djs.emplace(&djs[x],djs[x]);

    ans--;
    sz[y] += sz[x];
    djs[x] = y;
    return 1;
}

void undo() {
    *(stk_sz.top().X) = stk_sz.top().Y;
    *(stk_djs.top().X) = stk_djs.top().Y;
    stk_sz.pop();
    stk_djs.pop();
    ans++;
}

ll  t,n,m,q;
map<ll,ll> sp;
map<ll,ll> cnt;

struct node {
    ll l,r;
    node *lc,*rc;
    vector<ll> data;
};
node *root;

pii d[MAXN];
ll did;

node *build(ll l,ll r) {
    if (r == l+1) {
        return new node {l,r,0,0,vector<ll>()};
    }
    ll mid = (l + r) >> 1;
    return new node{l,r,build(l,mid),build(mid,r),vector<ll>()};
}

void insert_query(ll l,ll r,ll dd,node *nd) {
    if (l == nd->l && r == nd->r) {
        nd->data.emplace_back(dd);
        return;
    }
    ll mid = (nd->l + nd->r) >> 1;
    if (l >= mid) {
        insert_query(l,r,dd,nd->rc);
    } else if (r <= mid) {
        insert_query(l,r,dd,nd->lc);
    } else {
        insert_query(l,mid,dd,nd->lc);
        insert_query(mid,r,dd,nd->rc);
    }
}

void traversal(node *nd) {
    ll chg = 0;
    for (auto p : nd->data) {
        pii pa = d[p];
        if (uni(pa.X,pa.Y)) {
            chg++;
        }
    }
    if (nd->l == nd->r - 1) {
        if (nd->l >= 1 && nd->l <= q) {
            cout << ans << endl;
        }
    } else {
        traversal(nd->lc);
        traversal(nd->rc);
    }
    REP (i,chg) {
        undo();
    }
    delete nd;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cnt.clear();
        sp.clear();
        cin >> n >> m >> q;

        REP (i,m) {
            ll u,v;
            cin >> u >> v;
            if (u > v ) {
                swap(u,v);
            }
            cnt[u*1000000+v]++;
            sp[u*1000000+v] = 0;
        }

        root = build(0,q+2);
        init(n);

        REP1 (i,q) {
            char c;
            ll u,v;
            cin >> c >> u >> v;
            if (u > v) {
                swap(u,v);
            }
            if (c == 'N') {
                cnt[u*1000000+v]++;
                if (cnt[u*1000000+v] == 1) {
                    sp[u*1000000+v] = i;
                }
            } else {
                cnt[u*1000000+v]--;
                if (cnt[u*1000000+v] == 0) {
                    d[did++] = {u,v};
                    insert_query(sp[u*1000000+v],i,did-1,root);
                }
            }
        }
        for (auto E:cnt) {
            if (E.Y > 0) {
                d[did++] = {E.X/1000000,E.X%1000000};
                insert_query(sp[E.X],q+1,did-1,root);
            }
        }




        traversal(root);

    }
    return 0;
}
//TLE SF