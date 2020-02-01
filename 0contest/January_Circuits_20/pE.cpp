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
// const ll MAXN =

int n, k;

vector<array<int,5> > state;
vector<array<int,4> > cstate;
map<array<int,4>, int> cnt;
int rcnt[102];
vector<int> tran[102];
bool ban[102];

void build () {
    REP (a, 4) {
        REP (b, 4) {
            REP (c, 4) {
                REP (d, 4) {
                    REP (e, 4) {
                        array<int,4> cur = {};
                        cur[a]++;
                        cur[b]++;
                        cur[c]++;
                        cur[d]++;
                        cur[e]++;
                        cnt[cur]++;
                        cstate.pb(cur);
                    }
                }
            }
        }
    }

    sort(ALL(cstate));
    cstate.resize(unique(ALL(cstate))-cstate.begin());

    REP (i, SZ(cstate)) {
        rcnt[i] += cnt[cstate[i]];
    }
    REP (i, SZ(cstate)) {
        for (int K=0;K<4;K++) {
            if (cstate[i][K] > k) {
                ban[i] = true;
            }
        }
        REP (j, SZ(cstate)) {
            bool valid = true;
            for (int K=0;K<4;K++) {
                if (cstate[i][K]+cstate[j][K] > k) {
                    valid = false;
                }
            }

            if (valid) {
                tran[i].eb(j);
            }
        }
    }
}

ll dp[1003][57];
int main () {
    TIME(main);
    IOS();

    cin >> n >> k;
    {
        TIME(bd);
        build();
    }

    
    for (int i=0;i<SZ(cstate);i++) {
        if (!ban[i]) {
            dp[1][i] = 1;
        }
    }

    {
        TIME(dpc);
        int tk = 0;
        for (int i=2;i<=n;i++) {
            for (int j=0;j<SZ(cstate);j++) {
                if (!ban[j]) {
                    for (auto v : tran[j]) {
                        tk++;
                        dp[i][j] += dp[i-1][v] * rcnt[v] % MOD;
                        if (dp[i][j] >= MOD) {
                            dp[i][j] -= MOD;
                        }
                        // _OUTC(cerr, ALL(cstate[j]));
                        // _OUTC(cerr, ALL(cstate[v]));
                        // cerr<<endl;
                    }
                }
            }
        }
        debug(tk);
    }


    ll sum = 0;
    {
        TIME(fnl);
        for (int i=0;i<SZ(cstate);i++) {
            sum += dp[n][i] * rcnt[i] % MOD;
            sum %= MOD;
        }
    }
    cout << sum << endl;

    // #ifdef tmd
    // ll tmp = 0;
    // REP (i, SZ(cstate)) {
    //     for (auto v : tran[i]) {
    //         tmp += cnt[cstate[i]] * cnt[cstate[v]];
    //     }
    // }
    // cout << tmp << endl;
    // #endif
    return 0;
}
