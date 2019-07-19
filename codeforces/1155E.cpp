#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000003;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 11;

ll a[12][12], c[12], ans[12];
ll ja[12];
ll mpow(ll base,ll ep) {
    ep = ep % (MOD - 1);
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD;
        }
        base = base * base % MOD;
        ep >>= 1;
    }
    return ret;
}

void gen(ll r,ll x) {
    cout << "? " << x << endl;
    ll rt = 1;
#ifdef tmd
    ll bs = 1;
    REP (i, MAXN) {
        c[r] = (c[r] + ja[i] * bs) % MOD;
        bs = bs * x % MOD;
    }
#else
    cin >> c[r];
#endif
    REP (i, MAXN) {
        a[r][i] = rt;
        rt = rt * x % MOD;
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
#ifdef tmd
    REP (i, MAXN) {
        cin >> ja[i];
    }
    pary(ja, ja+MAXN);
#endif
    REP1 (i, MAXN) {
        gen(i-1, i);
    }
    REP (i, MAXN) {
        pary(a[i], a[i]+MAXN);
    }
    pary(c,c+MAXN);
    REP (i, MAXN) {
        for (ll j=i;j<MAXN;j++) {
            ll inv = mpow(a[j][i], MOD-2);
            REP (k, MAXN) {
                a[j][k] = a[j][k] * inv % MOD;
            }
            c[j] = c[j] * inv % MOD;
            if (j != i) {
                REP (k, MAXN) {
                    a[j][k] = (a[j][k] + MOD - a[i][k]) % MOD;
                }
                c[j] = (c[j] + MOD - c[i]) % MOD;
            }
        } 
    }
    REP (i, MAXN) {
        pary(a[i], a[i]+MAXN);
    }
    pary(c, c+MAXN);

    for (ll i=10;i>=0;i--) {
        ll sum = 0;
        for (ll j=i+1;j<=10;j++) {
            sum = (sum + ans[j] * a[i][j]) % MOD;
        }
        ans[i] = (c[i] - sum + MOD) % MOD;
    }
    pary(ans, ans + MAXN);

    REP (i, MOD) {
        ll sum = 0, bs = 1;
        REP (j, MAXN) {
            sum += ans[j] * bs % MOD;
            bs = bs * i % MOD;
            sum %= MOD;
        }
        if (sum == 0) {
            cout << "! " << i << endl;
            return 0;
        }
    }
    cout << "! " << -1 << endl;
    return 0;
}
