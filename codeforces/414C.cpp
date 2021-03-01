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
const ll MAXN = (1<<20) + 6;

ll n,m,q,dt[21],in[21];
bool st[21];
vector<ll> a[21];

ll bit[MAXN];
void add(ll pos,ll val) {
    for (;pos<MAXN;pos+=-pos&pos) {
        bit[pos] += val;
    }
}

ll query(ll pos) {
    ll ret = 0;
    for (;pos>=1;pos-=-pos&pos) {
        ret += bit[pos];
    }
    return ret;
}

ll inv(ll idx) {
    MEM(bit,0);
    ll ret = 0;
    for (auto x : a[idx]) {
        ret += query(MAXN-1) - query(x);
        add(x,1);
    }
    return ret;
}

vector<ll> v;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,(1<<n)) {
        ll d;
        cin >> d;
        v.eb(d);
        a[0].eb(d);
    }

    sort(ALL(v));
    v.resize(unique(ALL(v))-v.begin());
    for (auto &x : a[0]) {
        x = lower_bound(ALL(v),x) - v.begin() + 1;
    }

    in[0] = inv(0);
    REP1 (i,n) {
        a[i] = a[0];
        for (ll j=0;j<(1<<n-i);j++) {
            reverse(a[i].begin()+j*(1<<i),a[i].begin()+(j+1)*(1<<i));
        }
        in[i] = inv(i);
        dt[i] = in[i]-in[i-1];
        debug(a[i]);
        debug(inv(i));
    }

    pary(dt,dt+n+1);
    cin >> m;

    ll sum = in[0];
    while (m--) {
        ll lev;
        cin >> lev;
        REP1 (i,lev) {
            if (st[i]) {
                sum -= dt[i];
            } else {
                sum += dt[i];
            }
            st[i] = !st[i];
        }
        cout << sum << endl;
    }
    return 0;
}
