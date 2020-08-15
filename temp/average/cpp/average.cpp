#include <bits/stdc++.h>
#include "average.h"
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
const ll MAXN = 2e5 + 5;

struct Line {
    ll m, b;
};

ostream& operator << (ostream& os, const Line &l) {
    return os << "{" << l.m << "," << l.b << "}";
}
double inter (const Line &l1, const Line &l2) {
    return double(l2.b - l1.b) / double(l1.m - l2.m);
}

struct LC {
    vector<Line> lines;
    LC () {
    }

    double eval (Line mt) {
        if (lines.empty()) {
            return -1;
        }
        assert(lines.size());
        int l = -1, r = SZ(lines)-1;
        while (l < r - 1) {
            int m = (l+r) >> 1;
            double it = inter(lines[m], mt);
            if (m != SZ(lines)-1 && it >= inter(lines[m], lines[m+1])) {
                l = m;
            } else {
                r = m;
            }
        }
        return max({inter(lines[r],mt), inter(lines.front(), mt)});
    }

    void add (ll m, ll b) {
        Line nw({-m, b});

        while (SZ(lines) >= 2 && inter(lines.back(), lines[SZ(lines)-2]) > inter(lines.back(), nw)) {
            lines.pop_back();
        }
        lines.eb(nw);
    }
};

LC seg[MAXN*2+3];
void init() {
    for (int x=MAXN; x>=1; x>>=1) {
        seg[x].add(0, 0);
    }
}

ll sum, cnt;
Line lst;
void addMonth(int K) {
    sum += K;
    cnt++;
    for (int x=cnt+MAXN; x>=1; x>>=1) {
        seg[x].add(cnt, sum);
    }
    lst = Line({-cnt, sum});
}

double maximumAverage(int L, int R) {
    double res = 0;
    debug(L, R);
    debug(lst);
    for (L=L+MAXN, R=R+MAXN+1; L<R; L>>=1, R>>=1) {
        if (L&1) {
            debug(seg[L].lines);
            res = max(res, seg[L++].eval(lst));
        }
        if (R&1) {
            res = max(res, seg[--R].eval(lst));
            debug(seg[R].lines);
        }
    }
    return res;
}
