#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
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

vector<ll> pos[MAXN];
ll n,m,o[MAXN],p[MAXN],q,l[MAXN],r[MAXN],a[MAXN],ans[MAXN];
ll now_time;


ll BIT[MAXN];
ll query(ll x) {
    ll ret = 0;
    for (;x>=1;x-=-x&x) {
        ret += BIT[x];
    }
    return ret;
}
void add(ll L,ll R,ll val) {
    debug(L,R,val);
    for (;L<MAXN;L+=-L&L) {
        BIT[L] += val;
    }

    for (;R<MAXN;R+=-R&R) {
        BIT[R] -= val;
    }
}

ll sum(ll idx) {
    ll ret = 0;
    for (auto pp:pos[idx]) {
        ret += query(pp);
    }
    // debug(idx,pos[idx],ret);
    return ret;
}
void update(ll goal_time) {
    MEM(BIT,0);
    now_time = 0;
    while (goal_time > now_time) {
        now_time++;
        if (l[now_time] <= r[now_time]) {
            add(l[now_time],r[now_time]+1,a[now_time]);
        } else {
            add(l[now_time],m+1,a[now_time]);
            add(1,r[now_time]+1,a[now_time]);
        }
    }
}
void solve(vector<ll> V,ll L,ll R) {
    debug(V,L,R);
    if (SZ(V) == 0) return;
    if (L == R - 1) {
        for (auto v:V) {
            ans[v] = L;
        }
        return;
    }

    ll mid = L+R>>1;
    debug(mid);
    update(mid - 1);
    vector<ll> lV,rV;
    for (auto v:V) {
        debug(v,sum(v),mid);
        if (sum(v) >= p[v]) {
            lV.eb(v);
        } else {
            rV.eb(v);
        }
    }
    debug(lV,rV);
    solve(lV,L,mid);
    solve(rV,mid,R);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP1 (i,m) {
        cin >> o[i];
        pos[o[i]].eb(i);
    }

    REP1 (i,n) {
        cin >> p[i];
    }
    pary(p+1,p+n+1);

    cin >> q;
    REP1 (u,q) {
        cin >> l[u] >> r[u] >> a[u];
    }

    vector<ll> V;
    REP1 (i,n) {
        V.eb(i);
    }

    solve(V,1,q+2);
    REP1 (i,n) {
        if (ans[i] == q+1) {
            cout << "NIE" << endl;
        } else {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
