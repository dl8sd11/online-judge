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
const ll MAXN = 4e5 + 8;

ll n,a[MAXN],dp[MAXN][7];
inline ll poe(ll val) {
    if (val == 0) {
        return 2;
    } else {
        return val & 1;
    }
}

ll mn (vector<ll> idx,ll i) {
    ll ret = INF;
    for (auto x : idx) {
        ret = min(ret,dp[i][x]);
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> a[i];
    }

    dp[0][0] = 1 - (a[0] & 1);
    dp[0][1] = poe(a[0]);
    dp[0][2] = poe(a[0]);
    dp[0][3] = a[0];
    dp[0][4] = a[0];


    REP1 (i,n-1) {
        dp[i][0] = mn({0,1,3},i-1) + 1 - (a[i] & 1);
        dp[i][1] = mn({1,3},i-1) + poe(a[i]);
        dp[i][2] = mn({0,1,2,3},i-1) + poe(a[i]);
        dp[i][3] = dp[i-1][3] + a[i];
        dp[i][4] = mn({0,1,2,3,4},i-1) + a[i];
    }

    ll ans = INF;
    REP (i,5) {
        ans = min(ans,dp[n-1][i]);
    }

    REP (i,n) {
        pary(dp[i],dp[i]+5);
    }
    cout << ans << endl;
    return 0;
}
