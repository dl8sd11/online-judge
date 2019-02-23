#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
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

ll n,k;
string str;
vector<ll> h[30];
ll hei[MAXN];
ll cnt[30],fac[MAXN],inv[MAXN];

ll mypow(ll base,ll ep) {
    if (ep == 1) {
        return base;
    }
    ll tmp = mypow(base,ep>>1);
    tmp = tmp * tmp % MOD;
    return ep & 1 ? tmp * base % MOD : tmp;
}
void build() {
    fac[0] = 1;
    inv[0] = 1;
    for (ll i=1;i<MAXN;i++) {
        fac[i] = fac[i-1] * i % MOD;
        inv[i] = mypow(fac[i],MOD-2);
    }
}

ll C(ll N,ll R) {
    if (N < R) {
        return 0;
    }
    return fac[N] * inv[N-R] % MOD;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    build();
    cin >> str;
    for (auto c : str) {
        cnt[c-'a']++;
    }


    cin >> n >> k;
    REP (i,n) {
        char c;
        ll hi;
        cin >> c >> hi;
        h[c-'a'].emplace_back(hi);
        hei[i] = hi;
    }


    REP (i,26) {
        sort(ALL(h[i]));
    }

    sort(hei,hei+n);
    ll m = unique(hei,hei+n)-hei;

    REP (i,26) {
        if (h[i].size()) {
            debug(char(i+'a'),h[i]);
        }
    } 

    ll ans = 0;
    for (ll x=0;x<m;x++) {
        ll low = hei[x];
        ll G = 1,S = 1;
        REP (i,26) { // exact low
            G *= C(upper_bound(ALL(h[i]),low+k)-lower_bound(ALL(h[i]),low),cnt[i]);
            G %= MOD;
        }
        REP (i,26) {
            S *= C(upper_bound(ALL(h[i]),low+k)-lower_bound(ALL(h[i]),low+1),cnt[i]);
            S %= MOD;
        }

        ans += G - S;
        ans %= MOD;

        if (ans < 0) {
            ans += MOD;
        }
    }


    cout << ans << endl;
    return 0;
}
/*

nehs
5 10
h 8
s 15
e 4
s 9
n 14

kirino
10 7
i 5
n 4
n 10
o 9
i 11
i 3
i 6
r 7
k 8
r 2
*/