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
const ll MAXN = 200005;

int n, h[MAXN], s[MAXN];
vector<int> edge[MAXN];

int getDis (int v) {
    if (h[v] == -1) {
        cout << "d " << v << endl;
        cin >> h[v];
    }
    return h[v];
}

int getNext (int v) {
    if (s[v] == -1) {
        cout << "s " << v << endl;
        cin >> s[v];
    }
    return s[v];
}

int sz[MAXN], vis[MAXN], mx_sz[MAXN];
void getSZ (int nd, int par) {
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        if (v != par && !vis[v]) {
            getSZ(v, nd);
            sz[nd] += sz[v];
        }
    }
}

int getCen (int nd, int par, int tot) {
    int ret = -1;
    mx_sz[nd] = tot - sz[nd];
    for (auto v : edge[nd]) {
        if (v != par && !vis[v]) {
            int cur = getCen(v, nd, tot);
            if (ret == -1 || mx_sz[ret] > mx_sz[cur]) {
                ret = cur;
            }
            mx_sz[nd] = max(mx_sz[nd], sz[v]);
        }
    }

    if (ret == -1 || mx_sz[ret] > mx_sz[nd]) {
        ret = nd;
    }
    return ret;
}

int getCen (int rt) {
    getSZ(rt, rt);
    pary(sz+1, sz+n+1);
    int ret = getCen(rt, rt, sz[rt]);
    pary(mx_sz+1, mx_sz+n+1);
    return ret;
}

void ans (int x) {
    cout << "! " << x << endl;
}

int dep[MAXN], fat[MAXN];
void solve (int nd) {
    int cen = getCen(nd);
    vis[cen] = true;

    if (getDis(cen) == 0) {
        ans(cen);
    } else if (getDis(1) == dep[cen] + getDis(cen) - 1) {
        solve(getNext(cen));
    } else {
        solve(fat[cen]);
    }
}

void build (int nd, int par) {
    dep[nd] = dep[par] + 1;
    fat[nd] = par;
    for (auto v : edge[nd]) {
        if (v != par) {
            build(v, nd);
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    MEM(h, -1);
    MEM(s, -1);

    cin >> n;
    REP (i, n - 1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }
    build(1, 0);

    getDis(1);

    solve(1);

    return 0;
}
