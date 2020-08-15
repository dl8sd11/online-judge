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

struct Nd{
    int pri = rand();
    int val = 0, id = 0, sum = 0;
    Nd * lc=0, *rc = 0;
    Nd(int v, int pos) {
        val = sum=v; id = pos;
    }
};

inline void pull(Nd *&o) {
    if (!o)return;
    o->sum = o->val;
    if (o->lc) o->sum += o->lc->sum;
    if (o->rc) o->sum += o->rc->sum;
}

Nd * merge(Nd *A, Nd*B) {
    if (!A) return B;
    if (!B) return A;
    if (A->pri > B->pri) {
        A->rc = merge(A->rc, B);
        pull(A);
        return A;
    }else{
        B->lc = merge(A, B->lc);
        pull(B);
        return B;
    }
}

void split(Nd *o, Nd * & A, Nd *& B, int id) {
    A=B=0;
    if (!o) return;
    if (o -> id < id) {
        A = o;
        split(o->rc, A->rc, B, id);
        pull(A);
    }else{
        B = o;
        split(o->lc,A, B->lc, id);
        pull(B);
    }
}

Nd *bit[MAXN];

void ins (Nd *&nd, int id, int val) {
    Nd *lc, *rc;
    split(nd, lc, rc, id);
    nd = merge(merge(lc, new Nd(val, id)), rc);
}

ll pre (Nd *&nd, int x) {
    Nd *lc, *rc;
    split(nd, lc, rc, x+1);
    ll ret = lc ? lc->sum : 0;
    nd = merge(lc, rc);
    return ret;
}


void add_2d (int x, int y, int val) {
    for (x++; x<MAXN; x+=-x&x) {
        ins(bit[x], y, val);
    }
}

int pre_2d (int x, int y) {
    ll res = 0;
    for (x++; x>0; x-=-x&x) {
        res += pre(bit[x], y);
    }
    return res;
}
int n, q;
bool a[MAXN];

struct Event {
    int t, x, y, val, id;
};
vector<Event> events;

void CDQ (int L, int R) {

}

int cdq_t, cdq_q;
void add_cdq (int x, int y, int val) {
    events.push_back({cdq_t++, x, y, val, -1});

}


void add (int xl, int xr, int yl, int yr, int val) {
    add_2d(xl, yl, val);
    add_2d(xr+1, yl, -val);
    add_2d(xl, yr+1, -val);
    add_2d(xr+1, yr+1, -val);

    add_cdq(xl, yl, val);
    add_cdq(xr+1, yl, -val);
    add_cdq(xl, yr+1, -val);
    add_cdq(xr+1, yr+1, -val);
}

vector<int> ans_2d, ans_cdq;
void query (int x, int y) {
    cdq_q++;
    pre_cdq(x, y);
    ans_2d.eb(pre_2d(x, y));
}

/*
     0   1   2   3   4
       0   1   2   3
*/
set<int> off;
void toggle (int id, int t) {
    int lo = *prev(off.lower_bound(id));
    int ro = *off.upper_bound(id);
    if (a[id]) {
        add(lo+1, id, id+1, ro, t);
        off.insert(id);
    } else {
        add(lo+1, id, id+1, ro, -t);
        off.erase(id);
    }
    a[id] ^= 1;
}

signed main () {
    TIME(main);
    IOS();
    cin >> n >> q;

    off.insert(-1);
    off.insert(n);
    for (int i=0; i<n; i++) {
        off.insert(i);
    }
    for (int i=0; i<n; i++) {
        char c;
        cin >> c;
        if (c == '1') {
            toggle(i, 0);
        }
    }


    for (int i=1; i<=q; i++) {
        string str;
        cin >> str;
        if (str[0] == 'q') {
            int L, R;
            cin >> L >> R;
            L--, R--;
            int res = query(L, R);
            auto ptr = off.lower_bound(L);
            if (ptr == off.end() || (*ptr) >= R) { // conn
                res += i;
            }           
            cout << res << endl;
            
        } else {
            int x;
            cin >> x;
            x--;
            toggle(x, i);
        }
    }
    ans_cdq.resize(cdq_q);
    CDQ(0, cdq_t);
    
    return 0;
}
