#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmdd
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
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 2003;

int n;
int op[MAXN][MAXN];
int pre[MAXN][MAXN];

ll dp[MAXN][MAXN][2];

void build () {
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            pre[i][j] = op[i][j] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }
    }
}

int sum (int r1, int c1, int r2, int c2) {
    return pre[r2][c2] - pre[r1-1][c2] - pre[r2][c1-1] + pre[r1-1][c1-1];
}


ll mpow (ll bs, ll ep) {

    ll ret = 1;
    while (ep) {
        if (ep&1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

ll tw[MAXN*MAXN], iv[MAXN*MAXN];

void bpw () {
    ll i2 = mpow(2, MOD-2);
    tw[0] = iv[0] = 1;
    REP1 (i, MAXN*MAXN-1) {
        tw[i] = tw[i-1] * 2 % MOD;
        iv[i] = iv[i-1] * i2 % MOD;
    }
}

ll pw (ll ep) {
    return ep > 0 ? tw[ep] : iv[abs(ep)];
}
int main () {
    TIME(main);
    IOS();
    
#ifndef tmd
    freopen("sprinklers2.in", "r", stdin);
    freopen("sprinklers2.out", "w", stdout);
#endif

    cin >> n;

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            char ch;
#ifdef tmd
            
            op[i][j] = rand() % 5 != 0;

#else
            cin >> ch;
            op[i][j] = ch == '.';


#endif
        }
    }
    build();
    bpw();

    dp[0][0][1] = 1;
    dp[0][0][0] = 1;

    for (int j=1; j<=n; j++) {
        ll tot = 0;
        for (int i=0; i<=n; i++) {
            dp[i][j][1] = 0;
            
            ll dw = sum(i+1, j, n, j);
            if (op[i][j] && op[i+1][j]) {
                dp[i][j][1] += tot * pw(dw-2) % MOD;
                dp[i][j][1] %= MOD;
            }
            if (op[i][j]) {
                dp[i][j][0] += tot * pw(dw-1) %MOD;
                dp[i][j][1] %= MOD;
            }

            tot += dp[i][j-1][1];
            tot %= MOD;
            tot = tot * pw(sum(i+1, j, i+1, n)) % MOD;

            ll col = sum(i+1, j, n, j);

            if (op[i+1][j]) {
//                debug(i, j, col);
                dp[i][j][1] += dp[i][j-1][0] * pw(col-1) % MOD;
                dp[i][j][1] %= MOD;
            }
            dp[i][j][0] += dp[i][j-1][0] * pw(col) % MOD;
            dp[i][j][0] %= MOD;

            debug(i, j, dp[i][j][0], dp[i][j][1]);
        }
    }

    ll ans = 0;
    for (int i=0; i<=n; i++) {
        ans += dp[i][n][1];
        ans %= MOD;
    }
    ans += dp[n][n][0];
    ans %= MOD;

    cout << ans << endl;
    return 0;
}
