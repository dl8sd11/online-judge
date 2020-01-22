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
const ll MAXN = 303;
const ll MAXM = 602;

string s1, s2;
ll dp[MAXN][MAXN][MAXM], c[26];
ll n, m, w;

void ckmin (ll &x, ll y) {
    x = min(x, y);
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> m >> w;
    cin >> s1 >> s2;

    REP (i, 26) {
        cin >> c[i];
    }

    MEM(dp,INF);
    dp[0][0][0] = 0;
    REP (i, MAXN) {
        dp[i][0][0] = 0;
        dp[0][i][0] = 0;
    }

    assert(SZ(s1) == n);
    assert(SZ(s2) == m);
    assert(n > 0);
    assert(m > 0);
    REP (i, n+1) {
        REP (j, m+1) {
            REP (k, MAXM) {
                if (i > 0) {
                    ckmin(dp[i][j][k], dp[i-1][j][k]);
                }
                if (j > 0) {
                    ckmin(dp[i][j][k], dp[i][j-1][k]);
                }
                if (k > 0) {
                    if (i > 0 && j > 0 && s1[i-1] == s2[j-1]) {
                        ckmin(dp[i][j][k], dp[i-1][j-1][k-1]);
                    }

                    if (i > 0) {
                        ckmin(dp[i][j][k], dp[i-1][j][k-1]+c[s1[i-1]-'a']);
                    }
                    if (j > 0) {
                        ckmin(dp[i][j][k], dp[i][j-1][k-1]+c[s2[j-1]-'a']);
                    }
                }
            }
        }
    }

    ll mc = *min_element(c,c+26);

    ll ans = 0;

    // debug(dp[n][m][0]);
    // debug(dp[n][m][1]);
    // debug(dp[n][m][0]);
    // debug(dp[n][m][5]);
    // debug(dp[2][2][2]);
    // debug(dp[2][3][3]);

    mc *= 2;
    REP (i, MAXM) {
        ll sz = dp[n][m][i];
        if (w >= sz) {
            // debug(i, sz, i + (w-sz)/mc);
            ans = max(ans, i + (w-sz)/mc);
        }
    }

    cout << ans << endl;
    return 0;
}
