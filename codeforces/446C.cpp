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

const ll MOD = 1000000009;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 300005;
const ll K = sqrt(MAXN);


ll n,m,a[MAXN],pre[MAXN],f[MAXN],b[MAXN],fp[MAXN];
vector<pii> op;

inline void add(ll &x,ll y) {
    y %= MOD;
    x = (x + y) % MOD;
    x = (x + MOD) % MOD;
}

inline void sub(ll &x,ll y) {
    y %= MOD;
    x = (x - y) % MOD;
    x = (x + MOD) % MOD;
}

void build() {
    MEM(b,0);
    for (auto p : op) {
        add(b[p.X],1);
        if (p.Y + 1 <= n) {
            sub(b[p.Y+1],f[p.Y-p.X+2]);
            sub(b[p.Y+2],f[p.Y-p.X+1]);
        }
    }

    REP1 (i,n) {
        if (i > 1) {
            add(b[i],b[i-1] + b[i-2]); 
        }
        add(a[i],b[i]);
        pre[i] = a[i];
        add(pre[i],pre[i-1]);
    }
    op.clear();
}

ll calc(ll l,ll r) {
    ll ret = 0;
    for (auto p : op) {
        if (p.X < l) {
            if (p.Y >= l) {
                add(ret,fp[min(r,p.Y)-p.X+1] - fp[l-p.X]);
            }
        } else if (p.X <= r) {
            add(ret,fp[min(r,p.Y)-p.X+1]);
        }
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    fp[1] = f[1] = 1;
    REP1 (i,n) {
        cin >> a[i];
        if (i > 1) {
            f[i] = (f[i-1] + f[i-2]) % MOD; 
            add(fp[i],f[i]+fp[i-1]);
        }
        pre[i] = (a[i] + pre[i-1]) % MOD;
    }

    while (m--) {
        if (op.size() > K) {
            build();
        }
        
        ll cmd,l,r;
        cin >> cmd >> l >> r;
        if (cmd == 1) {
            op.eb(l,r);
        } else {
            cout << ((pre[r] - pre[l-1] + calc(l,r)) % MOD + MOD) % MOD << endl;
        }
    }
    return 0;
}
