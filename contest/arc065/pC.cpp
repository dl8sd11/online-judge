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
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;

vector<int> dv1, dv2;
int n, a, b, dis;
ll ans;

struct Point {
    int x, y, id;
    bool operator < (const Point & p1) {
        return pii(x, y) < pii(p1.x, p1.y);
    }
};
Point pt[MAXN];



int sz[MAXN];

int srch (int x, int y) {
    int l = -1, r = n;
    while (r > l + 1) {
        int m = (l + r) >> 1;
        if (pt[m].x > x || (pt[m].x == x && pt[m].y > y)) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

vector<int> edge[MAXN];
void connect (int d) {
    sort(pt, pt + n);

    int lst = -1;
    REP (i, n) {
        int rid = srch(pt[i].x+dis, pt[i].y+d);
        int lid = srch(pt[i].x+dis, pt[i].y-d-1);
    
        sz[pt[i].id] += rid - lid;
        lst = max(lst, lid);
        debug(lst, rid, pt[i].id);
        for (int j=lst; j<rid; j++) {
            edge[pt[i].id].eb(pt[j].id);
            edge[pt[j].id].eb(pt[i].id);
        }
        lst = rid - 1;
    }
}

bool vis[MAXN];
void dfs (int nd) {
    ans += sz[nd];
    debug(nd);
    vis[nd] = true;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> n;
    cin >> a >> b;
    a--, b--;
    REP (i, n) {
        pt[i].id = i;
        int x, y;
        cin >> x >> y;
        pt[i].x = x + y;
        pt[i].y = x - y;
    }

    dis = max(abs(pt[a].x - pt[b].x), abs(pt[a].y - pt[b].y));
    debug(dis);

    connect(dis);
    pary(sz, sz+n);
    REP (i, n) {
        swap(pt[i].x, pt[i].y);
    }
    connect(dis-1);
    pary(sz, sz+n);

    dfs(a);
    cout << ans << endl;
    return 0;
}
