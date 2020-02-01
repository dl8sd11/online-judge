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
const ll MAXN = 100003;

ll n;
vector<ll> px,py;
struct Event {
    ll l,r,y,w;
}e[MAXN*2];

struct Node {
    ll l,r;
    Node *lc,*rc;
    ll data,tag;

    ll get() {
        return data + tag;
    }

    void push() {
        if (lc && rc) {
            lc->tag += tag;
            rc->tag += tag;
        }
        data += tag;
        tag = 0;
    }

    void pull() {
        if (lc && rc) {
            data = max(lc->get(),rc->get());
        }
    }
};
Node *root;

Node *build(ll l,ll r) {
    if (r == l + 1) {
        return new Node {l,r,0,0,0,0};
    }
    ll mid = (l + r) >> 1;
    return new Node {l,r,build(l,mid),build(mid,r),0,0};
}

void add(ll l,ll r,ll val,Node *nd=root) {
    if (l == nd->l && r == nd->r) {
        nd->tag += val;
        return;
    }
    nd->push();
    ll mid = (nd->l + nd->r) >> 1;
    if (l >= mid) {
        add(l,r,val,nd->rc);
    } else if (r <= mid) {
        add(l,r,val,nd->lc);
    } else {
        add(l,mid,val,nd->lc);
        add(mid,r,val,nd->rc);
    }
    nd->pull();
}

ll query(ll l,ll r,Node *nd=root) {
    if (l == nd->l && r == nd->r) {
        return nd->get();
    }
    nd->push();
    ll mid = (nd->l + nd->r) >> 1;
    if (l >= mid) {
        return query(l,r,nd->rc);
    } else if (r <= mid) {
        return query(l,r,nd->lc);
    } else {
        return max(query(l,mid,nd->lc),query(mid,r,nd->rc));
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        ll px1,py1,px2,py2,w;
        cin >> px1 >> py1 >> px2 >> py2 >> w;
        e[i<<1] = {px1,px2,py1,-w};
        e[i<<1|1] = {px1,px2,py2+1,w};
        px.eb(px1);
        px.eb(px2);
        py.eb(py1);
        py.eb(py2+1);
    }

    sort(ALL(px));
    sort(ALL(py));
    px.resize(unique(ALL(px))-px.begin());
    py.resize(unique(ALL(py))-py.begin());

    root = build(0,SZ(px)+3);
    REP (i,n*2) {
        e[i].l = lower_bound(ALL(px),e[i].l) - px.begin();
        e[i].r = lower_bound(ALL(px),e[i].r) - px.begin();
        e[i].y = lower_bound(ALL(py),e[i].y) - py.begin();
        if (e[i].w > 0) {
            add(e[i].l,e[i].r+1,e[i].w);
        }
    }

    sort(e,e+n*2,[&](Event &e1,Event &e2){
        return e1.y < e2.y;
    });

    ll ptr = 0;
    ll sum = 0;
    ll ans = 0;
    debug(query(0,SZ(px)));
    REP (i,SZ(py)) {
        while (ptr < n*2 && e[ptr].y <= i) {
            add(e[ptr].l,e[ptr].r+1,e[ptr].w);
            sum += -e[ptr].w;
            ptr++;
        }
        ans = max(ans,sum+query(0,SZ(px)+3));
    }

    cout << ans << endl;
    return 0;
}
