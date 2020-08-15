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
template<typename _a> ostream &operator << (ostream &_s, const array<_a,2> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,3> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,4> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,5> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const set<_a> &_c) {return _OUTC(_s, ALL(_c));}
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
const ll MAXN = 3e5 + 5;

int n, q;

struct PB {
    int l, r;
    vector<int> qid;
};
int djs[MAXN], sz[MAXN];

void init () {
    for (int i=0; i<=n; i++) {
        djs[i] = i;
        sz[i] = 1;
    }
}

int fnd (int x) {
    return djs[x] == x ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    if (x == y) {
        return;
    }
    djs[x] = y;
    sz[y] += sz[x];
}
bool a[MAXN];
vector<pii> event;
vector<pii> qry;
signed main () {
    TIME(main);
    IOS();
    cin >> n >> q;
    for (int i=0; i<n; i++) {
        char c;
        cin >> c;
        a[i] = c == '1';
        if (a[i]) {
            event.eb(0, i);
        }
    }

    vector<int> tme;
    for (int i=1; i<=q; i++) {
        string str;
        cin >> str;
        if (str[0] == 'q') {
            int L, R;
            cin >> L >> R;
            L--, R--;
            qry.eb(L, R);
            tme.eb(i);
        } else {
            int x;
            cin >> x;
            x--;
            event.eb(i, x);
        }
    }


    queue<PB> bfs;
    vector<int> qids(SZ(qry));
    iota(ALL(qids), 0);
    
    bfs.push({-1, q+1, qids});
    int ptr = 0;

    init();
    vector<int> ans(SZ(qids));
    int lst = 0;
    while (bfs.size()) {
        PB cur = bfs.front();
        bfs.pop();

        debug(cur.l, cur.r, cur.qid);

        if (cur.l == cur.r - 1) {
            for (auto v : cur.qid) {
                ans[v] = max(0, tme[v] - cur.r);
            }
            continue;
        }

        int m = (cur.l + cur.r) >> 1;
        if (lst > m) {
            init();
            ptr = 0;
            lst = -1;
        }

        while (ptr < SZ(event) && event[ptr].X <= m) {
            debug(event[ptr]);
            mrg(event[ptr].Y, event[ptr].Y+1);
            lst = event[ptr].X;
            ptr++;
        }

        vector<int> pass, fail;
        for (auto v : cur.qid) {
            debug(qry[v].X, qry[v].Y);
            if (fnd(qry[v].X) == fnd(qry[v].Y)) {
                pass.eb(v);
            } else {
                fail.eb(v);
            }
        }

        bfs.push({cur.l, m, pass});
        bfs.push({m, cur.r, fail});
    }

    for (auto v : ans) {
        cout << v << endl;
    }
    
    return 0;
}
