#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
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
#define TIME(i) Timer i(#i)
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
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};

const ll MOD = 998244353;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 1003; 

int n, m;
vector<pair<ll, pii>> a;
ll dp[MAXN][MAXN];
ll isq, jsq, isu, jsu, dps;

ll mpow(ll base,ll ep) {
    ep = ep % (MOD - 1);
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD;
        }
        base = base * base % MOD;
        ep >>= 1;
    }
    return ret;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> m;
    REP (i, n) {
        REP (j, m) {
            ll d;
            cin >> d;
            a.eb(d, pii(i, j));
        }
    }

    sort(ALL(a));
    debug(a);
    int r, c;
    cin >> r >> c;

    ll idx = 0;
    for (auto el : a) {
        while (idx < SZ(a) && a[idx].X < el.X) {
            (isu += a[idx].Y.X) %= MOD; 
            (isq += SQ(a[idx].Y.X)) %= MOD; 
            (jsu += a[idx].Y.Y) %= MOD; 
            (jsq += SQ(a[idx].Y.Y)) %= MOD; 
            (dps += dp[a[idx].Y.X][a[idx].Y.Y]) %= MOD;
            idx++;
        }

        if (idx == 0){
            continue;
        }

        int i, j;
        tie(i, j) = el.Y; 
        debug(isq, jsq, isu, jsu);
        dp[i][j] = (dps + isq + SQ(i)*idx%MOD + jsq + SQ(j)*idx%MOD - isu*i*2%MOD -jsu*j*2%MOD)%MOD;
        debug(dp[i][j]);
        if (dp[i][j] < 0) {
            dp[i][j] += MOD;
        }
        (dp[i][j] *= mpow(idx, MOD-2)) %= MOD;
        debug(i, j, dp[i][j]);
        #ifdef tmd
        ll x, y;
        cin >> x >> y;
        assert(x*mpow(y, MOD-2)%MOD == dp[i][j]);

        #endif
    }

    cout << dp[r-1][c-1] << endl;
    return 0;
}