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
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 202;

ll n, K, a[MAXN], dp[2][MAXN][1003];
void add(ll &x, ll y) {
    x = (x + y) % MOD;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> K;
    REP (i,n) {
        cin >> a[i];
    }
    sort(a, a+n);

    dp[1][0][0] = 1;
    REP (i, n) {
        bool st = i & 1;
        REP (j, i+2) {
            REP (k, 1003) {
                ll cur = 0, d = i ? a[i] - a[i-1] : 0;
                if (j > 0 && k >= d * j) { // add to a open set
                    add(cur, dp[st^1][j][k-d*j]*j);
                }
                if (j > 0 && k >= d*(j-1)) { // add a open set
                    add(cur, dp[st^1][j-1][k-d*(j-1)]);
                }
                if (k >= d*j) {
                    add(cur, dp[st^1][j][k-d*j]); // add a close set
                }
                if (k >= d * (j+1)) { // close a set
                    add(cur, dp[st^1][j+1][k-d * (j+1)]*(j+1));
                }
                dp[st][j][k] = cur;
            }
        }
    }
    
    ll ans = 0;
    REP (i, K + 1) {
        add(ans, dp[n&1^1][0][i]);
    }

    cout << ans << endl;
    return 0;
}
