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
const ll MAXN = 10004;

int n, m, k;
vector<pii> lit;
vector<int> edge[MAXN*3];

int getID (int r, int c) {
    auto ptr = lower_bound(ALL(lit), pii(r, c));
    if (ptr == lit.end() || *ptr != pii(r, c)) {
        return -1;
    } else {
        return ptr - lit.begin();
    }
}

void build_row (int idx, int id) {
    if (id >= 1 && id <= m) {
        edge[idx].eb(k+n+id-1);
        edge[k+n+id-1].eb(idx);
    }
}

void build_col (int idx, int id) {
    if (id >= 1 && id <= n) {
        edge[idx].eb(k+id-1);
        edge[k+id-1].eb(idx);
    }
}

int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

int dis[MAXN*3];
bool vis[MAXN*3];
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> m >> k;
    REP (i, k) {
        int r, c;
        cin >> r >> c;
        lit.eb(r, c);
    }

    sort(ALL(lit));
    /* node id
    [0, k) = light
    [k, k+n) = row
    [k+n, k+n+m) = col


    */

    REP (i, k) {
        REP (d, 4) {
            int cx = lit[i].X + dx[d];
            int cy = lit[i].Y + dy[d];

            int id = getID(cx, cy);
            if (id != -1) {
                edge[i].eb(id);
            }


        }
        build_col(i, lit[i].X);
        build_row(i, lit[i].Y);
        build_col(i, lit[i].X+1);
        build_row(i, lit[i].Y+1);
        build_col(i, lit[i].X-1);
        build_row(i, lit[i].Y-1);
    }

    priority_queue<pii, vector<pii>, greater<pii> > pq;
    assert(lit[0] == pii(1, 1));
    MEM(dis, iNF);
    dis[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        pii cur = pq.top();
        pq.pop();
        if (vis[cur.Y]) {
            continue;
        }
        debug(cur);
        vis[cur.Y] = true;

        for (auto v : edge[cur.Y]) {
            int nd = dis[cur.Y] + (v >= k ? 1 : 0);
            if (nd < dis[v]) {
                dis[v] = nd;
                pq.emplace(nd, v);
            }
        }
    }
    debug(edge[9]);

    int bdis = getID(n, m) == -1 ? iNF : dis[getID(n, m)];
    int ans = min({dis[k+n-1], dis[k+n+m-1], bdis});
    debug(dis[k+n-1], dis[k+n+m-1], bdis);
    cout << (ans == iNF ? -1 : ans) << endl;
    return 0;
}
