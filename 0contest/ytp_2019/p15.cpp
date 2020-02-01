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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll MAXN = 

struct item {
    ll w,v;
} d[203];
ll dp[505][503];
/********** Good Luck :) **********/
int main()
{
    IOS();
    ll L,N,M;
    cin >> L >> N >> M;
    REP1 (i,N+M) {
        cin >> d[i].v >> d[i].w;
    }

    ll ans = 0;
    REP1 (i,N+M) {
        if (i>N) {
            for (ll j=L;j>=0;j--) {
                for (ll u=L;u>=0;u--) {
                    if (j-d[i].w >= 0) dp[j][u] = max(dp[j][u],dp[j-d[i].w][u] + d[i].v);
                    if (u-d[i].w >= 0) dp[j][u] = max(dp[j][u],dp[j][u-d[i].w] + d[i].v);
                    debug(j,u,dp[j][u]);
                    ans = max(ans,dp[j][u]);
                }
            }
        }
        else {
            for (ll j=0;j<=L;j++) {
                for (ll u=0;u<=L;u++) {
                    if (j-d[i].w >= 0 && u-d[i].w >= 0) dp[j][u] = max(dp[j][u],dp[j-d[i].w][u-d[i].w]+d[i].v*2);
                    else if (j-d[i].w >= 0) dp[j][u] = max(dp[j][u],dp[j-d[i].w][u]+d[i].v);
                    else if (u-d[i].w >= 0) dp[j][u] = max(dp[j][u],dp[j][u-d[i].w]+d[i].v);
                    ans = max(ans,dp[j][u]);
                }
            }
        }
        debug(dp[10][0]);
    }
    debug(dp[L][L]);
    cout << ans << endl;
    return 0;
}