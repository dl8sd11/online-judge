#include <bits/stdc++.h>
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx", "avx2")
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
const ll MAXN = 1003 + 5;

vector<string> ss;
struct Cor {
    array<int,3> ar;
    Cor () {

    }
    Cor (int a, int b, int c) {
        ar = {a, b, c};
    }
    bool operator < (const Cor &oth) const {
        return ar < oth.ar;
    }
    bool operator == (const Cor &oth) const {
        return ar == oth.ar;
    }
} cor[MAXN];

struct Hash {
    ll operator () (const Cor &c) const {
        return (ll(c.ar[0])<<24) ^ (c.ar[1]<<12) ^ (c.ar[2]);
    }
};
string nm[MAXN][3];

int uni (Cor a, Cor b) {
    set<int> cs;
    for (int i=0; i<3; i++) {
        cs.insert(a.ar[i]);
        cs.insert(b.ar[i]);
    }
    return cs.size();
}

void rotate (Cor &x) {
    Cor org = x;
    for (int i=0; i<3; i++) {
        x.ar[i] = org.ar[i==2?0:(i+1)];
    }
}

Cor mn (Cor c) {
    Cor ret = c;
    for (int i=0; i<2; i++) {
        rotate(c);
        ret = min(ret, c);
    }
    return ret;
}

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

unordered_set<Cor, Hash> st;

bool check (Cor A, Cor B) {
    int a, b, c, d, e, f;
    a = A.ar[0], b = A.ar[1], c = A.ar[2];
    d = B.ar[0], e = B.ar[1], f = B.ar[2];

    bool res = true;
    res &= st.find((Cor(e,b,f))) != st.end();
    res &= st.find((Cor(a,c,d))) != st.end();
    res &= st.find((Cor(d,c,e))) != st.end();
    res &= st.find((Cor(e,c,b))) != st.end();
    res &= st.find((Cor(b,a,f))) != st.end();
    res &= st.find((Cor(f,a,d))) != st.end();
    return res;
}
signed main () {
    TIME(main);
    IOS();
    freopen("laboratory.in", "r", stdin);
    freopen("laboratory.out", "w", stdout);

    int n;
    cin >> n;

    for (int i=0; i<n; i++) {
        for (int j=0; j<3; j++) {
            cin >> nm[i][j];
            ss.eb(nm[i][j]);
        }
    }
    sort(ALL(ss));
    ss.resize(unique(ALL(ss))-ss.begin());

    for (int i=0; i<n; i++) {
        for (int j=0; j<3; j++) {
            cor[i].ar[j] = lower_bound(ALL(ss), nm[i][j]) - ss.begin();
        }
    }

    st.reserve(4096);
    st.max_load_factor(0.25);

    for (int i=0; i<n; i++) {
        st.insert(cor[i]);
        for (int j=0; j<2; j++) {
            rotate(cor[i]);
            st.insert(cor[i]);
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (uni(cor[i], cor[j]) != 6) {
                continue;
            }
            for (int k=0; k<3; k++) {
                if (check(cor[i], cor[j])) {
                    cout << "YES" << endl;
                    debug(i, j);
                    return 0;
                }
                rotate(cor[j]);
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}
