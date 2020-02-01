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
const ll MAXN = 100005;

int n, k[MAXN];
vector<int> edge[MAXN];

bool vlock[MAXN];
int sz[MAXN];

void buildSZ (int nd, int par) {
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        if (v != par && !vlock[v]) {
            buildSZ(v, nd);
            sz[nd] += sz[v];
        }
    }
}

pair<int,int> getCen (int nd, int par, int up, int sum) {
    pair<int,int> ret = {MAXN, -1};

    int mx = up;
    for (auto v : edge[nd]) {
        if (v != par && !vlock[v]) {
            pair<int,int> cur = getCen(v, nd, sum-sz[v], sum);
            ret = min(cur, ret);

            mx = max(mx, sz[v]);
        }
    }

    ret = min(ret, {mx, nd});
    return ret;
}

int oneCentroid (int nd) {
    buildSZ(nd, nd);
    pair<int,int> ret = getCen(nd, nd, 0, sz[nd]);
    debug(ret.first, ret.second);
    return ret.second;
}

int bit[MAXN];

void add (int x, int val) {
    for (x++; x<MAXN; x+=-x&x) {
        bit[x] += val;
    }
}

int qry (int x) {
    int ret = 0;
    for (x++; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

void addDist (int nd, int par, int d, bool pos) {
    add(d, pos ? 1 : -1);
    debug(nd, d, pos);
    for (auto v : edge[nd]) {
        if (v != par && !vlock[v]) {
            addDist(v, nd, d + 1, pos);
        }
    }
}

int ans[MAXN];

void updateAns (int nd, int par, int d) {
    debug(nd, qry(k[nd]-d));
    ans[nd] += qry(k[nd]-d);
    for (auto v : edge[nd]) {
        if (v != par && !vlock[v]) {
            updateAns(v, nd, d+1);
        }

    }
}

void centroidDecomp (int nd) {

    int cen = oneCentroid(nd);
    vlock[cen] = true;

    for (auto v : edge[cen]) {
        if (!vlock[v]) {
            centroidDecomp(v);
        }
    }

    debug(cen);
    addDist(cen, cen, 0, true);
    ans[cen] += qry(k[cen]);


    for (auto v : edge[cen]) {
        if (!vlock[v]) {
            addDist(v, cen, 1, false);
            updateAns(v, cen, 1);
            addDist(v, cen, 1, true);
        }
    }

    addDist(cen, cen, 0, false);

    vlock[cen] = false;
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> k[i];
    }
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    centroidDecomp(1);

    REP1 (i, n) {
        cout << ans[i] << endl;
    }
    return 0;
}
