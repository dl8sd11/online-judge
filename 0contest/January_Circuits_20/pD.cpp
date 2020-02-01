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
const ll MAXN = 200005;

int n, V[MAXN];
vector<int> edge[MAXN];
vector<int> val[MAXN];

int in[MAXN], out[MAXN], tme, p[MAXN];
void dfs (int nd, int par) {
    p[nd] = par;
    in[nd] = tme++;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }
    out[nd] = tme;
}

int bit[MAXN];
void add (int x,int y) {
    for (x+=2;x<MAXN;x+=-x&x) {
        bit[x] += y;
    }
}

int qry (int x) {
    int ret = 0;
    for (x+=2;x>0;x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int qrySum (int l, int r) {
    return qry(r-1) - qry(l-1);
}

ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

ll tpw[MAXN], trv[MAXN];

void msub (ll &x, ll y) {
    x -= y;
    if (x < 0) {
        x += MOD;
    }
}

void madd (ll &x, ll y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}

ll sub1 (ll x) {
    return x == 0 ? MOD-1 : x-1;
}

ll cnt = 0, ans = 0;
void build (int nd) {
    ll sum = sub1(tpw[qrySum(in[nd], out[nd])]);

    debug(nd, qrySum(in[nd], out[nd]), in[nd], out[nd]);
    for (auto v : edge[nd]) {
        if (v != p[nd]) {
            msub(sum, sub1(tpw[qrySum(in[v], out[v])]));
            debug(v, qrySum(in[v], out[v]));
        }
    }
    madd(cnt, sum);
    madd(ans, sum*nd%MOD);
}


int main () {
    TIME(main);
    IOS();

    tpw[0] = 1;
    for (int i=1;i<MAXN;i++) {
        tpw[i] = tpw[i-1];
        madd(tpw[i], tpw[i-1]);
    }

    cin >> n;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1,0);
    REP1 (i, n) {
        cin >> V[i];
        val[V[i]].eb(i);
    }

    REP (i, MAXN) {
        for (auto v : val[i]) {
            build(v);
        }

        for (auto v : val[i]) {
            debug(in[v]);
            add(in[v], 1);
        }
    }

    ll sz = tpw[n] == 0 ? MOD-1 : tpw[n] - 1;
    msub(sz, cnt);
    madd(ans,sz);

    debug(ans);
    cout << ans * mpow(tpw[n], MOD-2) % MOD << endl;

    return 0;
}
