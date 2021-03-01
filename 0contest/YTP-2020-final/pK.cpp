#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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
#define f first
#define s second
#define MX(a,b) a=max(a,b)
#define MN(a,b) a=min(a,b)
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
const ll maxn = 4e3 + 5;

int zkw[maxn*2];

int bit[maxn][maxn];


int lowbit(int x){
    return x&(-x);
}

void ins(int x, int y, int val){
    x++, y++;
    for (int i=x;i<maxn;i+=lowbit(i)) {
        for (int j=y;j<maxn;j+=lowbit(j)) {
            bit[i][j] = max(bit[i][j],val);
        }
    }
}
ll qry(int x,int y) {
    x++, y++;
    ll ret = -(1e15+3);
    for (int i=x;i>0;i-=lowbit(i)) {
        for (int j=y;j>0;j-=lowbit(j)) {
            ret = max(bit[i][j],ret);
        }
    }
    return ret;
}
/*
    query: range max
    add: single change value
*/
void build () {
    for (int i=maxn-1; i>0; i--) {
        zkw[i] = max(zkw[i<<1], zkw[i<<1|1]);
    }
}

void chg (int x, int val) {
    x += maxn;
    for (zkw[x]=max(zkw[x], val); x>1; x>>=1) {
        zkw[x>>1] = max(zkw[x], zkw[x^1]);
    }
}

// int qry (int l, int r) {
//     int ret = -(1e15+3);
//     for (l+=maxn,r+=maxn; l<r; l>>=1, r>>=1) {
//         if (l&1) {
//             ret = max(ret, zkw[l++]);
//         }
//         if (r&1) {
//             ret = max(ret, zkw[--r]);
//         }
//     }
//     return ret;
// }


int a[maxn];
int dp[maxn][maxn];
vector<int> rk;

signed main () {
    TIME(main);
    IOS();
    for (int i = 0; i<maxn; ++i) for (int j = 0; j<maxn; ++j) bit[i][j] = -(1e15+3);
    int n;
    cin >> n;
    REP (i,n) {
        cin >> a[i];
        rk.eb(a[i]);
    }
    sort(ALL(rk));
    rk.resize(unique(ALL(rk)) - rk.begin());
    REP (i,n) {
        a[i] = int(lower_bound(ALL(rk),a[i]) - rk.begin() + 1);
    }

    // int nowmin = 1e9+5;
    int re = 0;
    for (int i = 0; i<n; ++i) {
        re = max(re, 1+qry(a[i]-1, a[i]-1));
        for (int j = i+1; j<n; ++j) {
            if (a[j] < a[i]) {
                // if (a[j] <= nowmin) continue;
                dp[i][j] = 2+qry(a[i]-1, a[j]-1);
                debug(i,j,dp[i][j]);
            }
        }
        
        for (int k = 0; k<i; ++k) {
            if (a[k] > a[i]) {
                if (dp[k][i])
                    ins(a[k], a[i],dp[k][i]);
            }
        }
        ins(a[i], a[i],1);
        // nowmin = min (nowmin, a[i]);
    }
    debug(re);
    // assert(re % 2 == 0);
    cout<<re<<endl;
    return 0;
}
