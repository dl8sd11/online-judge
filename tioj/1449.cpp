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
const ll MAXN = 1003;

ll n,k,a[MAXN],w[MAXN][MAXN];
ll dp[MAXN][MAXN],pi[MAXN][MAXN];

ll solve(ll idx,ll p,ll lst) {
    return dp[lst][p-1] + w[lst+1][idx];
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    REP1 (i,n-1) {
        cin >> a[i+1];
    }
    sort(a+1,a+n+1);

    REP1 (l,n) {
        ll ptr = l,sum = 0;
        for (ll r=l;r<=n;r++) {
            sum += a[r] - a[ptr];
            if (ptr < (l+r)/2) {
                ll dis = a[ptr+1] - a[ptr];
                sum -= (r-ptr)*dis;
                sum += (ptr-l+1)*dis;
                ptr++;
            }
            w[l][r] = sum;
        }
    }

    REP1 (i,n) {
        dp[i][1] = w[1][i];
        pi[i][1] = 0;
    }
    REP1 (j,k) {
        if (j == 1) {
            continue;
        }
        for (ll i=n;i>=0;i--) {
            for (ll t=pi[i][j-1];t<=(i==n?n:pi[i+1][j]);t++) {
                if (solve(i,j,t) < solve(i,j,pi[i][j])) {
                    pi[i][j] = t;
                }
            }
            dp[i][j] = solve(i,j,pi[i][j]);
        }
    }

    cout << dp[n][k] << endl;
    return 0;
}
