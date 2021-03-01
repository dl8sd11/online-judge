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

const ll MOD = 989327761;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 102;

int n, a[MAXN], dp[MAXN][MAXN*MAXN];
int cnt[MAXN];

int c[MAXN][MAXN];

void build () {
    c[0][0] = 1;
    REP1 (i, MAXN-1) {
        c[i][0] = 1;
        REP1 (j, MAXN-1) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
        }
    } 
}

set<int> gp;
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
 
    dp[0][0] = 1;
    build();
    cin >> n;

    int sum = 0;
    REP1 (i, n) {
        cin >> a[i];
        gp.insert(a[i]);
        for (int k=MAXN-1; k>=1; k--) {
            for (int j=MAXN*MAXN-1; j>=a[i]; j--) {
                dp[k][j] += dp[k-1][j-a[i]];
                dp[k][j] %= MOD;
            }
        }
        cnt[a[i]]++;
        sum += a[i];
    }
    debug(sum);
    debug(dp[16][1205-200]);

    if (SZ(gp) == 1 || SZ(gp) == 2) {
        cout << n << endl;
        return 0;
    }

    int ans = 0;
    REP1 (i, MAXN-1) {
        REP1 (j, cnt[i]) {
            if (dp[j][i * j] == c[cnt[i]][j]) {
                debug(i, j);
                ans = max(ans, j);
            }
        }

        REP (j, cnt[i]) {
            if (dp[n-(cnt[i]-j)][sum - (cnt[i] - j) * a[i]] == c[cnt[i]][j]) {
                debug(i, j, cnt[i]-j);
                ans = max(ans, cnt[i]-j);
            }
        }

    }

    cout << ans << endl;
    return 0;
}
