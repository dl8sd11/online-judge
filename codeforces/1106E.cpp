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
const ll MAXN = 100003;

ll n,m,k;
pii a[MAXN];
struct Event {
    ll d,w,type;
    
};


vector<Event> event[MAXN];

map<pii,int,greater<pii> > es;

ll dp[MAXN][230];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m >> k;
    REP (i,k) {
        ll s,t,d,w;
        cin >> s >> t >> d >> w;
        event[s].push_back({d,w,1});
        event[t+1].push_back({d,w,-1});
    }

    REP1 (i,n) {
        for (auto e : event[i]) {
            if (e.type == 1) {
                es[{e.w,e.d}]++;          
            } else {
                if (--es[{e.w,e.d}] == 0) {
                    es.erase({e.w,e.d});
                }
            }
        }
        if (es.size()) {
            a[i] = (*es.begin()).X;
        } else {
            a[i] = {0,i};
        }
    }

    pary(a+1,a+1+n);

    es.clear();

    MEM(dp,0x3f);
    dp[1][0] = 0;
    REP1 (i,n) {
        REP (j,m+1) {
            dp[i+1][j+1] = min(dp[i+1][j+1],dp[i][j]);
            dp[a[i].Y+1][j] = min(dp[a[i].Y+1][j],dp[i][j]+a[i].X);
        }
        debug(a[i]);
        debug(dp[i][0],dp[i][1]);
    }

    ll ans = INF;
    REP (j,m+1) {
        ans = min(ans,dp[n+1][j]);
    }

    cout << ans << endl;

    
    return 0;
}
