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
// const ll MAXN = 
const ll N = 30,K = 20,M = 10000;
ll n,m,k;
vector<ll> v;
ll dp[N][K][M],mx[N][K][M],mn[N][K][M];

void prt(vector<pii> opt) {
    REP (i,SZ(opt)) {
        cout << opt[i].X << "x" << opt[i].Y << ",\n"[i==SZ(opt)-1];
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    // ugly input
    string l1;
    getline(cin,l1);
    stringstream ss0;
    ss0 << l1;
    ss0 >> n >> m;
    string s;
    getline(cin,s);
    stringstream ss;
    ss << s;
    ll d;
    assert(n<=20&&k<=15&&m<=1000);
    debug(n,s);
    while (ss>>d) {
        v.eb(d);
    }
    v.eb(-1);
    reverse(ALL(v));
    k = SZ(v);

    ll sum = 0;
    dp[0][0][0] = 1;
    MEM(mn,INF);
    REP1 (j,k-1) {
        dp[0][j][0] = 1;
        REP1 (i,n) {
            REP1 (w,m) {
                for (ll a=0;i-a>=0&&a*v[j]<=w;a++) {
                    dp[i][j][w] += dp[i-a][j-1][w-a*v[j]];
                    if (dp[i-a][j-1][w-a*v[j]]) {
                        mx[i][j][w] = max(mx[i][j][w],a);
                        mn[i][j][w] = min(mn[i][j][w],a);
                    }
                }
            }
        }
    }


    cout << dp[n][k-1][m] << endl;
    if (dp[n][k-1][m]) {
        ll tr = m, tn = n;
        vector<pii> ans;
        for (ll i=k-1;i>=0;i--) {
            if (mx[tn][i][tr] > 0) {
                ans.eb(v[i],mx[tn][i][tr]);
                ll cnt = mx[tn][i][tr];
                tn -= cnt;
                tr -= v[i]*cnt;
            }
        }
        prt(ans);

        tr = m, tn = n;
        ans.clear();
        for (ll i=k-1;i>=0;i--) {
            if (mn[tn][i][tr] != INF && mn[tn][i][tr]) {
                ans.eb(v[i],mn[tn][i][tr]);
                ll cnt = mn[tn][i][tr];
                tn -= cnt;
                tr -= v[i]*cnt;
            }
        }
        prt(ans);
    }
    return 0;
}
