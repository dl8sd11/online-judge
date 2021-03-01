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
const ll MAXN = 200005;

ll n,k,dp[MAXN][10];
vector<ll> da[4];

ll one(bool dbl) {
    ll ret = -1;
    if (!da[3].empty()) {
        ret = max(ret,da[3][0] * (dbl ? 2 : 1));
    }
    if (!da[1].empty()) {
        ret =  max(ret,da[1][0] * (dbl ? 2 : 1));
    }
    if (!da[2].empty()) {
        ret = max(ret,da[2][0] * (dbl ? 2 : 1));
    }
    return ret;
}

ll two(bool dbl) {
    ll ret = -1;
    if (SZ(da[1]) >= 2) {
        ret = max(ret,da[1][0] * (dbl ? 2 : 1) + da[1][1]);
    }
    if (SZ(da[1]) >= 1 && SZ(da[2]) >= 1) {
        ret = max(ret,da[1][0] + da[2][0] + (dbl ? max(da[1][0],da[2][0]) : 0));
    }
    return ret;
}

ll three(bool dbl) {
    ll ret = -1;
    if (SZ(da[1]) >= 3) {
        ret = max(ret,da[1][0] * (dbl ? 2 : 1) + da[1][1] + da[1][2]);
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,MAXN) {
        REP (j,10) {
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;
    REP1 (i,n) {
        cin >> k;
        REP (j,k) {
            ll c,d;
            cin >> c >> d;
            da[c].eb(d);
        }
        REP1 (idx,3) {
            sort(da[idx].rbegin(),da[idx].rend());
            debug(da[idx]);
        }
        
        REP (j,10) {
            dp[i][j] = dp[i-1][j];
            if (one(j==0) != -1) {
                dp[i][j] = max(dp[i][j],dp[i-1][(j+9)%10] + one(j==0));
            }
            if (two(j < 2) != -1) {
                dp[i][j] = max(dp[i][j],dp[i-1][(j+8)%10] + two(j < 2));
            }
            if (three(j < 3) != -1) {
                dp[i][j] = max(dp[i][j],dp[i-1][(j+7)%10] + three(j < 3));
            }
        }
        pary(dp[i],dp[i]+10);
        REP1 (idx,3) {
            da[idx].clear();
        }
    }

    ll ans = 0;
    REP (i,10) {
        ans = max(ans,dp[n][i]);
    }
    cout << ans << endl;
    return 0;
}
