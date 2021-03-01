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

const ll MOD = 998244353;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 51;

ll n,m,w[MAXN];
bool like[MAXN];

ll mpow(ll base,ll ep) {
    ep %= MOD - 1;
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
void add(ll &x,ll y) {
    x = (x + y) % MOD;
}
ll frac(ll x,ll y) {
    assert(y > 0);
    return x * mpow(y,MOD-2) % MOD;
}
ll dp[MAXN][MAXN][MAXN],op,on;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n) {
        cin >> like[i];
    }
    REP (i,n) {
        cin >> w[i];
        if (like[i]) {
            op += w[i];
        } else {
            on += w[i];
        }
    }

    REP (el,n) {
        MEM(dp,0);
        dp[0][0][0] = 1;
        if (like[el]) {
            for (ll i=1;i<=m;i++) {
                for (ll dx=0;dx<=i;dx++) {
                    for (ll dw=0; dw<=dx;dw++) {
                        ll cp = dx + op, cn = on - i + dx, cw = dw + w[el];
                        if (cn >= 0) {
                            add(dp[i][dx][dw],dp[i-1][dx][dw]*frac(cn+1,cp+cn+1));
                            if (dx > 0) {
                                add(dp[i][dx][dw],dp[i-1][dx-1][dw]*frac(cp-1,cp+cn-1)%MOD*frac(cp-cw-1,cp-1));
                            }
                            if (dw > 0 && dx > 0) {
                                add(dp[i][dx][dw],dp[i-1][dx-1][dw-1]*frac(cp-1,cp+cn-1)%MOD*frac(cw-1,cp-1));
                            }
                        }
                    }
                }
            }
            ll ans = 0;
            for (ll dx=0;dx<=m;dx++) {
                for (ll dw=0;dw<=dx;dw++) {
                    add(ans,(dw+w[el])*dp[m][dx][dw]);
                }
            }
            cout << ans << endl;
        } else {
            for (ll i=1;i<=m;i++) {
                for (ll dx=0;dx<=i;dx++) {
                    for (ll dw=0; dw<=dx;dw++) {
                        ll cp = op + i - dx, cn = on - dx, cw = w[el] - dw;
                        if (cn >= 0 && cw >= 0 && cn >= cw) {
                            if (cp > 1) {
                                add(dp[i][dx][dw],dp[i-1][dx][dw]*frac(cp-1,cp+cn-1));
                            }
                            if (dx > 0) {
                                add(dp[i][dx][dw],dp[i-1][dx-1][dw]*frac(cn+1,cp+cn+1)%MOD*frac(cn+1-cw,cn+1));
                            }
                            if (dw > 0 && dx > 0) {
                                add(dp[i][dx][dw],dp[i-1][dx-1][dw-1]*frac(cn+1,cp+cn+1)%MOD*frac(cw+1,cn+1));
                            }
                        }
                    }
                }
            }
            ll ans = 0;
            for (ll dx=0;dx<=m;dx++) {
                for (ll dw=0;dw<=dx;dw++) {
                    if (dw < w[el]) {
                        add(ans,(w[el]-dw)*dp[m][dx][dw]);
                    }
                }
            }
            cout << ans << endl;
        }
    }

    
    return 0;
}
