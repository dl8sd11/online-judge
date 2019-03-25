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

vector<ll> pos;

ll n;
struct Seg {
    ll l,r,w;
}seg[MAXN];

struct Node{
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
    return new Node{l,r,build(l,mid),build(mid,r),0,0};
}

void add(ll l,ll r,ll val,Node *nd=root) {
    if (l == nd->l && r == nd->r) {
        nd->tag += val;
        return;
    }
    ll mid = (nd->l + nd->r) >> 1;
    nd->push();
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
        cin >> seg[i].l >> seg[i].r >> seg[i].w;
        pos.emplace_back(seg[i].l);
        pos.emplace_back(seg[i].r);
    }

    sort(ALL(pos));
    pos.resize(unique(ALL(pos))-pos.begin());

    vector<ll> id;
    REP (i,SZ(pos)) {
        if (i == 0 ) {
            id.eb(0);
        } else if (pos[i] == pos[i-1] + 1) {
            id.eb(id.back()+1);
        } else {
            id.eb(id.back()+2);
        }
    }

    REP (i,n) {
        seg[i].l = id[(lower_bound(ALL(pos),seg[i].l)-pos.begin())];
        seg[i].r = id[(lower_bound(ALL(pos),seg[i].r)-pos.begin())];
    }

    sort(seg,seg+n,[&](Seg s1,Seg s2) {
        return s1.l < s2.l;
    });

    root = build(0,id.back()+10);
    ll ptr = 0;

    ll ans = 0;
    REP (i,id.back()+10) {
        while (ptr < n && seg[ptr].l <= i) {
            debug(seg[ptr].l,seg[ptr].r+1,seg[ptr].w,i);
            add(0,seg[ptr].r+1,seg[ptr].w);
            ptr++;
        }
        ans = max(ans,query(0,i+1));
    }

    cout << ans << endl;

    return 0;
}
 