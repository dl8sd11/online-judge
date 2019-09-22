#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

const int MOD = 998244353;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 200005;
const int MAXC = 1000006;

int n, a[MAXN], inv[MAXC];
int divi[MAXN][256], dcnt[MAXN];
int sum[MAXC], dp[256];

int mpow(ll base,int ep) {
    int ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD;
        }
        base = base * base % MOD;
        ep >>= 1;
    }
    return ret;
}

void add (int &x, int y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}
void sub (int &x, int y) {
    x -= y;
    if (x < 0) {
        x += MOD;
    }
}

int dl[251], dr[251], lc, rc;
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    

    cin >> n;
    REP (i, n) {
        cin >> a[i];
        lc = rc = dcnt[i] = 0;
        for (int j=1; j*j<= a[i]; j++) {
            if (a[i] % j == 0) {
                if (inv[j] == 0) {
                    inv[j] = mpow(j, MOD-2);
                }
                add(sum[j], a[i]);
                dl[lc++] = j;
                if (j * j != a[i]) {
                    int k = a[i] / j;
                    dr[rc++] = k;
                    add(sum[k], a[i]);
                    if (inv[k] == 0) {
                        inv[k] = mpow(k, MOD-2);
                    }
                }
            }
        }
        REP (j, lc) {
            divi[i][dcnt[i]++] = dl[j];
        }
        RREP (j, rc-1) {
            divi[i][dcnt[i]++] = dr[j];
        }
        
    }

    int ans = 0;
    REP (i, n) {
        RREP (x, dcnt[i]-1) {
            dp[x] = sum[divi[i][x]];
            for (int y=x+1; y<dcnt[i]; y++) {
                if (divi[i][x] != divi[i][y] && divi[i][y] % divi[i][x] == 0) {
                    sub(dp[x], dp[y]);
                }
            }
            int cur = dp[x];
            if (a[i] == divi[i][x]) {
                sub(cur, a[i]);
            }
            add(ans, ll(cur)*inv[divi[i][x]]%MOD*a[i]%MOD);
        }
    }

    cout << ll(ans) * inv[2] % MOD << endl;

    return 0;
}
