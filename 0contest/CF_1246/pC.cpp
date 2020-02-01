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

int n, m;
ll dp[MAXN][MAXN][2], dpre[MAXN][MAXN][2];
char rk[MAXN][MAXN];
ll rkv[MAXN][MAXN], rkh[MAXN][MAXN];

ll nml (ll x) {
    if (x >= MOD) {
        x -= MOD;
    } else if (x < 0) {
        x += MOD;
    }
    return x;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> m;
    REP (i, n) {
        REP (j, m) {
            cin >> rk[i][j];
        }
    }

    RREP (i, n-1) {
        RREP (j, m-1) {
            rkv[i][j] = rkv[i+1][j] + (rk[i][j] == 'R');
            rkh[i][j] = rkh[i][j+1] + (rk[i][j] == 'R');
        }
    }


    RREP (i, n-1) {
        RREP (j, m-1) {
            if (i == n-1 && j == m-1) {
                dpre[i][j][0] = dpre[i][j][1] = dp[i][j][0] = dp[i][j][1] = (rk[i][j] == '.');
            } else {
                { // 0
                    ll cur = nml(dpre[i][j+1][1] - dpre[i][m-rkh[i][j+1]][1]);
                    dp[i][j][0] = cur;
                }
                { // 1
                    ll cur = nml(dpre[i+1][j][0] - dpre[n-rkv[i+1][j]][j][0]);
                    dp[i][j][1] = cur;
                }
                dpre[i][j][0] = nml(dpre[i+1][j][0] + dp[i][j][0]);
                dpre[i][j][1] = nml(dpre[i][j+1][1] + dp[i][j][1]);
            }
        }
    }


    if (n == 1 && m == 1) {
        cout << dp[0][0][0] << endl;
    } else {
        cout << (dp[0][0][0] + dp[0][0][1]) % MOD << endl;
    }

#ifdef tmd
    int x, y;
    while (cin >> x >> y) {
        debug(dp[x][y][0], dp[x][y][1]);
    }
#endif

    return 0;
}
