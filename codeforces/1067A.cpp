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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=998244353;
const ll MAXN=1e5+5;

ll n,a[MAXN],dp[MAXN][205][2],sum0,sum1;
void add(ll &num,ll delta) {
    num = (num + delta) % MOD;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin>>n;
    REP1 (i,n) {
        cin >> a[i];
    }

    REP1 (i,n) {
        if (i==1) {
            if (a[i] == -1) {
                REP1 (j,200) {
                    dp[i][j][0] = 1;
                }
            } else {
                dp[i][a[i]][0] = 1;
            }
            continue;
        }
        ll pref[205],preb = 0;
        pref[0] = 0;
        REP1 (j,200) {
            if (j) {
                pref[j] = pref[j-1];
            }
            add(pref[j],dp[i-1][j][0]);
            add(pref[j],dp[i-1][j][1]);
        }
        for (ll j=200;j>=1;j--) {
            if (a[i] == -1 || a[i] == j) {
                add(dp[i][j][0],pref[j-1]);
                add(dp[i][j][1],preb+dp[i-1][j][0]+dp[i-1][j][1]);
            }
            preb = (preb + dp[i-1][j][1]) % MOD;
        }
        
    }

    ll ans = 0;
    REP1 (i,200) {
        add(ans,dp[n][i][1]);
    }

    cout << ans << endl;
    return 0;
}
