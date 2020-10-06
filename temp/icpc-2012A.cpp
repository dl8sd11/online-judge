#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double, double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) static_cast<int>(i.size())
#define FOR(i, j, k, in) for (int i=j; i < (k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j; i >= (k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(), _a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
template<typename T, typename S>
istream &operator >> (istream &is, pair<T, S> &p) {
    return is >> p.X >> p.Y;
}
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do {\
    fprintf(stderr, "%s - %d (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<" ,"; _do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << "," << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":",")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _a, size_t _b> ostream &operator << (ostream &_s, const array<_a,_b> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s, const map<_a,_b> &_c) {return _OUTC(_s,ALL(_c));}
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
const ll MAXN = 52; 
/*
 (x-y) + (vx - vy)t
 */

vector<array<int,3>> p, v;
int n;
vector<int> pos, id;
vector<tuple<double, int, int>> events;
vector<pii> edge;

void make_event (int a, int b) {
    double t2 = 0, t1 = 0, c = 0;

    double sgn = 1;
    for (int cur : {a, b}) {
        int x, y;
        tie(x, y) = edge[cur];
        for (int i=0; i<3; i++) {
            t2 += sgn * SQ(v[x][i] - v[y][i]);
            t1 += 2 * sgn * (v[x][i] - v[y][i]) * (p[x][i] - p[y][i]);
            c += sgn * SQ(p[x][i] - p[y][i]);
        }
        sgn *= -1;
    }
    double va = SQ(t1) - 4*t2*c;
    if (t2 == 0) {
        if (t1 != 0) {
            events.push_back({-c/t1, a, b});
        }
    } else if (va == 0) {
        events.push_back({-t1/(2*t2), a, b});
    } else if (va > 0) {
        events.push_back({(-t1+sqrt(va))/(2*t2), a, b});
        events.push_back({(-t1-sqrt(va))/(2*t2), a, b});
    }
}

double dis (int z, double t) {
    int x, y;
    tie(x, y) = edge[z];
    double sq = 0;
    for (int i=0; i<3; i++) {
        sq += SQ((p[x][i] + v[x][i]*t) - (p[y][i] + v[y][i]*t));
    }
    return sq;
}

int djs[MAXN], sz[MAXN];
int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

bool mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) return false;
    if (sz[x] > sz[y]) swap(x, y);
    djs[x] = y;
    sz[y] += sz[x];
    return true;
}

double sort_t;
bool by_dis (int i, int j) {
    return i == j ? false : dis(i, sort_t) < dis(j, sort_t);
}

vector<int> mst (vector<int> e_can, double t) {
    sort_t = t;
    sort(ALL(e_can), by_dis);
    for (int i=0; i<n; i++) {
        djs[i] = i;
        sz[i] = 1;
    }
    vector<int> ret;
    for (auto eid : e_can) {
        int x, y;
        tie(x, y) = edge[eid];
        if (mrg(x, y)) {
            ret.eb(eid);
        }
    }

    sort(ALL(ret));
    return ret;
}

void print_all (double t) {
    debug(t);
    for (int i=0; i<SZ(edge); i++) {
        debug(i, dis(i, t));
    }
}
signed main () {
    TIME(main);
    IOS();

    int ts = 0;
    while (cin >> n && n > 0) {
        ts++;

        v.clear();
        p.clear();
        edge.clear();
        events.clear();
        for (int i=0; i<n; i++) {
            int x, y, z, vx, vy, vz;
#ifdef tmd
            x = rand() % 100;
            y = 0; 
            z = rand() % 100;
            vx = 0;
            vy = 0;
            vz = -1;

#else
            cin >> x >> y >> z >> vx >> vy >> vz;
#endif
            p.push_back({x, y, z});
            v.push_back({vx, vy, vz});
        }

        for (int i=0; i<n; i++) {
            for (int j=0; j<i; j++) {
                edge.eb(i, j);
            }
        }
        for (int i=0; i<SZ(edge); i++) {
            for (int j=0; j<i; j++) {
                make_event(i, j);
            }
        }

        sort(ALL(events));
        for (auto &[t, x, y] : events) {
            debug(t, x, y);
        }

        id.resize(SZ(edge));
        iota(ALL(id), 0);
        
        sort_t = 0;
        sort(ALL(id), by_dis);

        vector<int> imst(SZ(edge), 0);
        vector<int> prv = mst(id, 0);
        for (int e : prv) imst[e] = true;
        debug(prv);
        print_all(0);

        int ans = 0;
        for (auto &[t, x, y] : events) {
            if (t < 0) {
                continue;
            }
            vector<int> cur = prv;
            cur.eb(x);
            cur.eb(y);

            t += 1e-7;
            //print_all(t);
            if ((imst[x] ^ imst[y]) == 0) {
                continue;
            }
            vector<int> nw = mst(cur, t);
            debug(nw);
            if (nw != prv) {
                for (int e : prv) imst[e] = false;
                ans++;
                prv = nw;
                for (int e : prv) imst[e] = true;
            }
        }

        cout << "Case " << ts << ": " << ans+1 << endl;
    }
    return 0;
}

