#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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

ll n,m,a[MAXN];

struct node {
    node *lc,*rc;
    ll l,r;
    ll data;
};

node *build(ll l,ll r) {
    if (r == l+1) {
        return new node{0,0,l,r,a[l]};
    }
    ll mid = (l + r) >> 1;
    return new node{build(l,mid),build(mid,r),l,r,0};
}

ll query(ll l,ll r,node *nd) {
    if (l == nd->l && r == nd->r) {
        return nd->data;
    }
    ll mid = (nd->l + nd->r) >> 1;
    if (l >= mid) {
        return query(l,r,nd->rc);
    } else if (r <= mid) {
        return query(l,r,nd->lc);
    } else {
        return query(l,mid,nd->lc) + query(mid,r,nd->rc);
    }
}

node *add(ll pos,ll val,node *nd) {
    node *ret = new node(*nd);
    if (nd->l == pos && nd->r == pos+1) {
        ret->data += val;
    } else {
        ll mid = (ret->l + ret->r) >> 1;
        if(pos >= mid) {
            ret->rc = add(pos,val,nd->rc);
        } else {
            ret->lc = add(pos,val,nd->lc);
        }
        ret->data = ret->lc->data + ret->rc->data;
    }
    return ret;
}

node *root[1000003];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    
    root[0] = build(0,n+1);
    REP1 (i,n) {
        cin >> a[i];
        root[i] = add(a[i],1,root[i-1]);
    }

    REP (i,m) {
        ll al,ar,vl,vr;
        cin >> al >> ar >> vl >> vr;
        cout << query(vl,vr+1,root[ar]) - query(vl,vr+1,root[al-1]) << endl;
    }
    return 0;
}
