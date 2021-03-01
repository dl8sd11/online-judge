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
const ll MAXN = 100005;

bool lucky(ll num) {
    while (num > 0) {
        if (num % 10 != 4 && num % 10 != 7) {
            return false;
        }
        num /= 10;
    }
    return true;
}

ll fc[MAXN],ifc[MAXN];
ll mpow(ll base,ll ep) {
    if (ep == 0) {
        return 1;
    }
    ll hf = mpow(base,ep>>1);
    hf = hf * hf % MOD;
    return ep & 1 ? hf * base % MOD : hf;
}
void build() {
    fc[0] = ifc[0] = 1;
    REP1 (i,MAXN-1) {
        fc[i] = fc[i-1] * i % MOD;
        ifc[i] = mpow(fc[i],MOD-2);
    }
}
ll c(ll m,ll r) {
    return fc[m] * ifc[r] % MOD * ifc[m-r] % MOD;
}
ll n,k,ul;
map<ll,ll> lk;
/********** Good Luck :) **********/
int main()
{
    IOS();
    build();
    cin >> n >> k;
    REP (i,n) {
        ll num;
        cin >> num;
        if (lucky(num)) {
            lk[num]++;
        } else {
            ul++;
        }
    }

    ll ls = SZ(lk);
    vector<ll> dp(ls+1);
    dp[0] = 1;
    for (auto p : lk) {
        for (ll i=ls;i>=1;i--) {
            dp[i] = (dp[i] + dp[i-1]*p.Y) % MOD;
        }
    }

    ll ans = 0;
    for (ll i=0;i<=ls;i++) {
        if (k-i >= 0 && k-i <= ul) {
            ans += dp[i] * c(ul,k-i) % MOD;
            ans %= MOD;
        }
    }

    cout << ans << endl;
    return 0;
}
