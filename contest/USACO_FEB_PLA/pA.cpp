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
const ll MAXN=2e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,m;

struct Shot{
    ll x,y,d;
}shot[MAXN];

struct Query{
    ll a,b,id;
   
}query[MAXN];
bool cmps (const Shot &s1,const Shot &s2) {
    return s1.x < s2.x;
}
bool cmpq  (const Query &q1,const Query &q2) {
    return q1.a < q2.a;
}
struct Zkwtree {
    ll seg[MAXN*2];
    void init () {
        REP (i,MAXN*2) {
            seg[i] = INF;
        }
    }

    ll query (ll l,ll r) {
        ll ret = INF;
        for (l+=MAXN,r+=MAXN;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret = min(ret,seg[l++]);
            }
            if (r&1) {
                ret = min(ret,seg[--r]);
            }
        }
        return ret;
    }

    void add (ll pos,ll val) {
        pos+=MAXN;
        seg[pos] = min(seg[pos],val);
        for (;pos>1;pos>>=1) {
            seg[pos>>1] = min(seg[pos],seg[pos^1]);
        }
    }
}treep,treen;

ll ans[MAXN];
vector<ll> yval;
map<ll,ll> ymap;
/********** Good Luck :) **********/
int main()
{
    #ifndef tmd
        freopen("slingshot.in","r",stdin);
        freopen("slingshot.out","w",stdout);
    #endif

    IOS();
    cin >> n >> m;
    REP (i,n) {
        cin >> shot[i].x >> shot[i].y >> shot[i].d;
        yval.eb(shot[i].y);
    }
    sort(shot,shot+n,cmps);

    REP (i,m) {
        cin >> query[i].a >> query[i].b;
        query[i].id = i;
        ans[i] = abs(query[i].a - query[i].b);
        yval.eb(query[i].b);
    }

    sort(query,query+m,cmpq);

    sort(ALL(yval));
    yval.resize(unique(ALL(yval))-yval.begin());
    REP (i,SZ(yval)) {
        ymap[yval[i]] = i;
    }
    
    treep.init(); // shotY > queryY
    treen.init(); // shotY < queryY
    ll ptr = -1;
    REP (i,m) {
        while (ptr+1 < n && shot[ptr+1].x <= query[i].a) {
            ptr++;
            debug(ptr);
            treep.add(ymap[shot[ptr].y],shot[ptr].d - shot[ptr].x + shot[ptr].y);
            treen.add(ymap[shot[ptr].y],shot[ptr].d - shot[ptr].x - shot[ptr].y);
        }
        ans[query[i].id] = min(ans[query[i].id],treep.query(ymap[query[i].b],MAXN)+query[i].a-query[i].b);
        ans[query[i].id] = min(ans[query[i].id],treen.query(0,ymap[query[i].b])+query[i].a+query[i].b);
    }

    treep.init();
    treen.init();
    ptr = n;
    RREP (i,m-1) {
        while (ptr-1 >= 0 && shot[ptr-1].x >= query[i].a) {
            ptr--;
            debug(ptr);
            debug(shot[ptr].x,shot[ptr].y,shot[ptr].d);
            treep.add(ymap[shot[ptr].y],shot[ptr].d + shot[ptr].x + shot[ptr].y);
            treen.add(ymap[shot[ptr].y],shot[ptr].d + shot[ptr].x - shot[ptr].y);
        }
        debug(treep.query(ymap[query[i].b],MAXN));
        debug(treen.query(0,ymap[query[i].b]));
        ans[query[i].id] = min(ans[query[i].id],treep.query(ymap[query[i].b],MAXN)-query[i].a-query[i].b);
        ans[query[i].id] = min(ans[query[i].id],treen.query(0,ymap[query[i].b])-query[i].a+query[i].b);
    }

    REP (i,m) {
        cout << ans[i] << endl;
    }
    return 0;
}

/*
4 2
2 0 10
8 6 2
7 2 0
8 4 8
8 8
5 1

1 1
7 2 0
5 1
4

*/