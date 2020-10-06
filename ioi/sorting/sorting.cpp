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
#include "sorting.h"

int n;
vector<int> org, fnl, pos;
vector<pii> opr, res;

void change (int pa, int pb) {
    swap(fnl[pa], fnl[pb]);
    swap(pos[fnl[pa]], pos[fnl[pb]]);
}
bool solve (int cnt) {
    fnl = org;
    for (int i=0; i<cnt; i++) {
        swap(fnl[opr[i].X], fnl[opr[i].Y]);
    }
    debug(cnt, fnl);
    pos.resize(n);
    for (int i=0; i<n; i++) {
        pos[fnl[i]] = i;
    }

    vector<pii> swp;
    for (int i=0; i<n; i++) {
        if (fnl[i] != i) {
            swp.eb(i, fnl[i]);
            int ot = fnl[i];
            swap(fnl[pos[i]], fnl[i]);
            pos[ot] = pos[i];
            pos[i] = i;
        }
    }
    debug(swp);

    fnl = org;
    for (int i=0; i<n; i++) {
        pos[fnl[i]] = i;
    }
    if (swp.size() > cnt) return false;
    res.clear();
    for (int i=0; i<cnt; i++) {
        change(opr[i].X, opr[i].Y);        
        int pa = 0, pb = 0;
        if (i < SZ(swp)) {
            pa = pos[swp[i].X];
            pb = pos[swp[i].Y];
        }
        change(pa, pb);
        res.eb(pa, pb);
    }


    return true;
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    n = N;
    for (int i=0; i<N; i++) {
        org.eb(S[i]);
    }
    for (int i=0; i<M; i++) {
        opr.eb(X[i], Y[i]);
    }

    int L = -1, R = M;
    while (L < R - 1) {
        int M = (L + R) >> 1;
        if (solve(M)) R = M;
        else L = M;
    }

    solve(R);
    debug(R, res.size());
    assert(res.size() == R);
    for (int i=0; i<R; i++) {
        tie(P[i], Q[i]) = res[i];
    }
    debug(R);
	return R;
}


