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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0X7F7F7F7F;
const ll MAXN = 2003;
const int MAXW = 100005;

int a, n, m;
bool rain[MAXN];
int dp[2][MAXW];
set<int> ub[MAXN];
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> a >> n >> m;
    REP (i, n) {
        int l, r;
        cin >> l >> r;
        for (int ps=l+1; ps<=r; ps++) {
            rain[ps] = true;
        }
    }

    REP (i, m) {
        int p, w;
        cin >> p >> w;
        ub[p].insert(w);
    }

    REP (i, a+1) {
        ub[i].insert(0);
    }

    MEM(dp, iNF);
    for (auto u : ub[0]) {
        dp[0][u] = 0;
    }

    REP1 (i, a) {
        int p = (i&1) ^ 1;
        REP (j, MAXW) {
            int &cur = dp[i&1][j];
            cur = iNF;
            if (rain[i]) {
                if (ub[i].count(j)) {
                    for (int k=1; k<MAXW-1; k++) {
                        if (dp[p][k] != iNF) {
                            cur = min(cur, dp[p][k] + k);
                        }
                    }
                } else {
                    if (dp[p][j] != iNF) {
                        cur = min(cur, dp[p][j]+j);
                    }
                }
            } else {
                if (ub[i].count(j)) {
                    if (i == 8 && j == 1) {
                        debug(dp[p][2]);
                    }
                    for (int k=0; k<MAXW-1; k++) {
                        if (dp[p][k] != iNF) {
                            cur = min(cur, dp[p][k]);
                        }
                    }
                } else {
                    if (dp[p][j] != iNF) {
                        cur = min(cur, dp[p][j]+j);
                    }
                }
            }
        }
        pary(dp[i&1], dp[i&1] + 12);
    }

    int ans = iNF;

    REP (i, MAXW) {
        ans = min(dp[a&1][i], ans);
    }

    cout << (ans == iNF ? -1 : ans) << endl;
    return 0;
}
