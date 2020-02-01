#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
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
const int iNF = 0x3f3f3f3f;
const int MAXN = 51;

int n, m, k, a, b, cc_cnt;
bool vis[MAXN];
int dep[MAXN], low[MAXN];
vector<int> edge[MAXN];

vector<pii> edge_stk;
vector<pii> CC[MAXN * 2];
void dfs (int nd, int par) {
    low[nd] = dep[nd] = dep[par] + 1;
    vis[nd] = true;

    for (auto v : edge[nd]) {
        if (v == par) {
            continue;
        } else if (vis[v]) {
            if (dep[v] < dep[nd]) { // back edge
                edge_stk.eb(v, nd);
                low[nd] = min(low[nd], dep[v]);
            }
        } else {
            edge_stk.eb(v, nd);
            dfs(v, nd);
            if (low[v] >= dep[nd]) {
                pii p = edge_stk.back();
                edge_stk.pop_back();
                while (p != pii(v, nd)) {
                    CC[cc_cnt].eb(p);
                    p = edge_stk.back();
                    edge_stk.pop_back();
                }
                CC[cc_cnt++].eb(p);
            }
            low[nd] = min(low[nd], low[v]);
        }
    }
}

ll dp[MAXN*2][MAXN*2], cc_dp[MAXN*2];

void build_dp () {
    dp[0][0] = 1;
    REP1 (i, MAXN*2 - 1) {
        REP1 (j, k) {
            REP (l, j+1) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-l]) % MOD;
            }
            cc_dp[i] = (cc_dp[i] + dp[i][j]) % MOD;
        }
    }
}

ll mpow(ll base,ll ep) {
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


ll burn_side (int sz) {
    ll sum = 0;
    REP (i, sz) {
        ll gcd = __gcd(i, sz);
        sum += mpow(k, gcd);
        sum %= MOD;
    }
    return sum * mpow(sz,MOD - 2) % MOD;
}
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();
    cin >> n >> m >> k;
    build_dp();

    REP (i, m) {
        cin >> a >> b;
        edge[a].eb(b);
        edge[b].eb(a);
    }

    REP1 (i, n) {
        if (!vis[i]) {
            dfs(i, i);
        }
    }

    ll ans = 1;
    REP (i, cc_cnt) {
        set<int> vert;
        for (auto v : CC[i]) {
            vert.insert(v.X);
            vert.insert(v.Y);
        }
        debug(CC[i]);

        if (SZ(vert) == 2) {
            ans = ans * k % MOD;
        } else if (SZ(vert) == SZ(CC[i])) {
            ans = ans * burn_side(SZ(CC[i])) % MOD;
            debug(burn_side(SZ(CC[i])));
        } else {
            ans = ans * cc_dp[SZ(CC[i])] % MOD;
            debug(cc_dp[SZ(CC[i])]);
        }
    }

    cout << ans << endl;
    return 0;
}
