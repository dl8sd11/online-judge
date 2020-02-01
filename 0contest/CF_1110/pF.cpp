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
const ll MAXN=5e5+5;
const ll MAXLG=__lg(MAXN)+2;


namespace SEG {
    ll a[MAXN];
    struct node {
        ll l,r;
        node *lc,*rc;
        ll d, da;
        node (ll li, ll ri, node *lci,node *rci,ll di,ll dai):l(li),r(ri),lc(lci),rc(rci),d(di),da(dai){}
    };
    node *root;
    node *build (ll l,ll r) {
        if (r==l+1) return new node(l,r,0,0,a[l],0);
        ll mid = (l+r)/2;
        node *tlc = build(l,mid);
        node *trc = build(mid,r);
        return new node(l,r,tlc,trc,min(tlc->d,trc->d),0);
    }
    ll query(ll l,ll r,node *now=root) {
        if (now->l==l&&now->r==r) return now->da+now->d;
        ll mid = (now->l+now->r)/2;
        if (r<=mid) return now->da+query(l,r,now->lc);
        if (l>=mid) return now->da+query(l,r,now->rc);
        else return now->da+min(query(l,mid,now->lc),query(mid,r,now->rc));
    }
    void mody(ll l,ll r, ll data,node *now=root) {
        if (now->l==l&&now->r==r) {
            now->da += data;
            return;
        }
        ll mid = (now->l+now->r)/2;
        if (r<=mid) {
            mody(l,r,data,now->lc);
            now->d = min(now->lc->da+now->lc->d,now->rc->da+now->rc->d);
            return;
        }
        if (l>=mid) {
            mody(l,r,data,now->rc);
            now->d = min(now->lc->da+now->lc->d,now->rc->da+now->rc->d);
            return;
        }
        mody(l,mid,data,now->lc);
        mody(mid,r,data,now->rc);
        now->d = min(now->lc->da+now->lc->d,now->rc->da+now->rc->d);
    }
}

struct Query {
    ll id,l,r;
};
ll n,q;
vector<pii> edge[MAXN];
vector<Query> query[MAXN];

vector<pii> leaf; //id,dist
ll out[MAXN],ans[MAXN];
ll ts;
void build_dist(ll nd,ll par,ll dis) {
    ts++;
    if (edge[nd].size() == 1) {
        leaf.emplace_back(nd,dis);
    }
    for (auto v : edge[nd]) {
        if (par != v.X) {
            build_dist(v.X,nd,dis+v.Y);
        }
    }
    out[nd] = ts;
}
void DFS(ll nd,ll par,ll len) {
    SEG::mody(0,SZ(leaf),len);
    ll l = lower_bound(ALL(leaf),make_pair(nd,-1LL)) - leaf.begin();
    ll r = lower_bound(ALL(leaf),make_pair(out[nd]+1,-1LL)) - leaf.begin();
    SEG::mody(l,r,-len*2);
    for (auto Q : query[nd]) {
        l = lower_bound(ALL(leaf),make_pair(Q.l,-1LL)) - leaf.begin();
        r = lower_bound(ALL(leaf),make_pair(Q.r+1,-1LL)) - leaf.begin();
        debug(Q.id,SEG::query(l,r),l,r);
        ans[Q.id] = SEG::query(l,r);
    }
    for (auto v : edge[nd]) {
        if (v.X != par) {
            DFS(v.X,nd,v.Y);
        }
    }
    SEG::mody(0,SZ(leaf),-len);
    l = lower_bound(ALL(leaf),make_pair(nd,-1LL)) - leaf.begin();
    r = lower_bound(ALL(leaf),make_pair(out[nd]+1,-1LL)) - leaf.begin();
    SEG::mody(l,r,len*2);
    
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;
    REP (i,n-1) {
        ll v,w;
        cin >> v >> w;
        edge[i+2].emplace_back(v,w);
        edge[v].emplace_back(i+2,w);
    }


    REP (i,q) {
        ll v,l,r;
        cin >> v >> l >> r;
        query[v].push_back({i,l,r});
    }
    build_dist(1,1,0);
    pary(out+1,out+n+1);

    REP (i,SZ(leaf)) {
        SEG::a[i] = leaf[i].Y;
    }

    debug(leaf);
    SEG::root = SEG::build(0,leaf.size());

    debug(SEG::query(0,SZ(leaf)));

    DFS(1,1,0);

    REP (i,q) {
        cout << ans[i] << endl;
    }
    return 0;
}
