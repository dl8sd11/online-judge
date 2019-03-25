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
const ll MAXN = 200003;

ll n,k;
ll a[MAXN],dp[MAXN][4];

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;

    dp[0][0] = 1; // x y
    dp[0][1] = 0; // x x
    dp[0][2] = 1; // -1 -1
    dp[0][3] = 1; // -1 x
    REP1 (i,MAXN-1) {
        if (i == -1) {
            dp[i][0] = k-2;
            dp[i][1] = k-1;
            dp[i][2] = k;
            dp[i][3] = k-1;
        } else {
            dp[i][0] = (dp[i-1][0]*(k-2) + dp[i-1][1]) % MOD;
            dp[i][1] = dp[i-1][0] * (k-1) % MOD;
            dp[i][2] = dp[i-1][2] * (k-1) % MOD;
            dp[i][3] = dp[i-1][3] * (k-1) % MOD;
        }
    }


    vector<ll> odd,even;
    REP (i,n) {
        cin >> a[i];
        if (i&1) {
            odd.eb(a[i]);
        } else {
            even.eb(a[i]);
        }
    }

    ll ans = 1;
    ll lsto = -1,lste = -1;

    REP (i,SZ(odd)+1) {
        if (i == SZ(odd) || odd[i] != -1) {
            if (lsto == -1) {
                if (i == SZ(odd)) {
                    ans = ans * dp[i-lsto-1][2] % MOD;
                } else {
                    ans = ans * dp[i-lsto-1][3] % MOD;
                }
            } else {
                if (i == SZ(odd)) {
                    ans = ans * dp[i-lsto-1][3] % MOD;
                } else if (odd[lsto] == odd[i]) {
                    ans = ans * dp[i-lsto-1][1] % MOD;
                } else {
                    ans = ans * dp[i-lsto-1][0] % MOD;
                }
            }
            lsto = i;
        }
    }

    REP (i,SZ(even)+1) {
        if (i == SZ(even) || even[i] != -1) {
            if (lste == -1) {
                if (i == SZ(even)) {
                    ans = ans * dp[i-lste-1][2] % MOD;
                } else {
                    ans = ans * dp[i-lste-1][3] % MOD;
                }
            } else {
                if (i == SZ(even)) {
                    ans = ans * dp[i-lste-1][3] % MOD;
                } else if (even[lste] == even[i]) {
                    ans = ans * dp[i-lste-1][1] % MOD;
                } else {
                    ans = ans * dp[i-lste-1][0] % MOD;
                }
            }
            lste = i;
        }
    }

    cout << ans << endl;
    return 0;
}
