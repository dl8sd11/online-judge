#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=(k) ; i-=in)
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
const ll N = 16;

ll n,m;
ll dp[1<<N][N],sum[1<<N],dis[N][N];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    MEM(dis,-1);
    REP (i,m) {
        ll u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        dis[u][v] = w;
        dis[v][u] = w;
    }

    sum[0] = 0;
    REP (st,1<<n) {
        REP (i,n) {
            if ((st>>i) & 1) {
                ll tmp = 0;
                REP (j,n) {
                    if (dis[i][j] != -1 && (st&(1<<j))) {
                        tmp += dis[i][j];
                    }
                }
                sum[st] = tmp + sum[st-(1<<i)];
                break;
            }
        }
    }


    ll ans = INF;

    MEM(dp,-INF);
    dp[1][0] = 0;
    REP (st,1<<n) {
        REP (t,n) {
            if (st&(1<<t)) {
                // new bridge
                REP (np,n) {
                    if (t != np && (st&(1<<np)) == 0 && dis[t][np] != -1) {
                        dp[st+(1<<np)][np] = max(dp[st+(1<<np)][np],dp[st][t] + dis[t][np]);
                    }
                }

                // new set

                ll rev = (1<<n) - st - 1;
                for (ll sub=rev;sub>0;sub=(sub-1)&rev) {
                    dp[st+sub][t] = max(dp[st+sub][t],dp[st][t] + sum[sub+(1<<t)]);
                }
            }
        }
        ans = min(ans,sum[(1<<n)-1]-dp[st][n-1]);
    }
    debug(sum[(1<<n)-1]);
    cout << ans << endl;
    return 0;
}
