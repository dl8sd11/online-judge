#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx", "avx2", "fma")
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

const int MOD = 1000000009;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int C = 910607;
const int C2 = 880301;
const int MOD2 = 1000000007;

const ll MAXN = 5003;

int dp[MAXN][MAXN], dp2[MAXN][MAXN];

char res[MAXN];
int ans[MAXN], ans2[MAXN], len;
int cp[MAXN], cp2[MAXN];

string s;
int main () {
    TIME(main);
    IOS();

    cin >> s;

    int n = s.size();
    int sz = (1<<(__lg(n)))-1;
    sz = n - sz;

    cp[0] = 1;
    for (int i=1; i<=n; i++) {
        cp[i] = 1LL * cp[i-1] * C % MOD;
        cp2[i] = 1LL * cp2[i-1] * C2 % MOD2;
        res[i-1] = 'z';
    }

    dp[0][0] = 0;
    for (int i=1; i<=n; i++) {
        dp[i][0] = 0;

        char c = s[i-1];
        for (int j=1; j<=min(i,sz); j++) {
            if (j+n-i < sz) {
                continue;
            }
            dp[i][j] = -1;

            debug(i, j, len, dp[i-1][j-1], ans[j-1], c, res[j-1]);
            if ((j-1==len ||c < res[j-1]) && j-1 <= len && dp2[i-1][j-1] == ans2[j-1] && dp[i-1][j-1] == ans[j-1]) {
                res[j-1] = c;
                len = j;
                ans[j] = (1LL*cp[j]*c + ans[j-1]) % MOD;
                ans2[j] = (1LL*cp2[j]*c + ans2[j-1]) % MOD2;
                dp[i][j] = ans[j];
                dp2[i][j] = ans2[j];
            }
            if (c == res[j-1] && j-1 < len && dp2[i-1][j-1] == ans2[j-1] && dp[i-1][j-1] == ans[j-1]) {
                dp[i][j] = ans[j];
                dp2[i][j] = ans2[j];
            }
            for (int k=1; i-k-j>=0; k<<=1) {
                int rem = i-k-j;
                if ((rem & k) == 0 && j <= len && dp2[i-k][j] == ans2[j] && dp[i-k][j] == ans[j]) {
                    dp[i][j] = dp[i-k][j];
                    dp2[i][j] = dp2[i-k][j];
                }
            }

            debug(dp[i][j]);
            pary(res, res+len);

        }
    } 

    for (int i=0; i<len; i++) {
        cout << res[i];
    }
    cout << endl;

    return 0;
}
