#include <algorithm>
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
#include "teams.h"

const int MAXN = 500005;
int n;

struct Node {
    Node *lc, *rc;
    int sz;
    Node ():lc(0), rc(0), sz(0) {}
};
Node mem[MAXN*40], *root[MAXN];
int node_cnt;

Node* get_new () {
    return &mem[node_cnt++];
}

Node* get_new (Node *nd) {
    mem[node_cnt] = *nd;
    return &mem[node_cnt++];
}

Node *build (int l, int r) {
    if (r == l + 1) {
        return get_new();
    }
    int m = (l + r) >> 1;
    Node *nd = get_new();
    nd->lc = build(l, m);
    nd->rc = build(m, r);
    return nd;
}

Node *ins (int nL, int nR, int *elm, int sz, Node *nd) {
    Node *res = get_new(nd);
    res->sz += sz;
    if (nL < nR-1) {
        int nM = (nL + nR) >> 1;
        int ls = lower_bound(elm, elm+sz, nM) - elm;
        if (ls) res->lc = ins(nL, nM, elm, ls, res->lc);
        if (sz-ls) res->rc = ins(nM, nR, elm+ls, sz-ls, res->rc);
    }
    return res;
}

int qry (int nL, int nR, int x, Node *nd) {
    if (x <= nL) return nd->sz;
    if (x >= nR) return 0;
    int nM = (nL + nR) >> 1;
    return qry(nL, nM, x, nd->lc) + qry(nM, nR, x, nd->rc);
}

int qry(Node* lnd, Node *rnd, int x) {
    int res = qry(1, n+1, x, rnd) - qry(1, n+1, x, lnd);
    return res;
}

int cur[MAXN];
vector<pii> rng;
void init(int N, int A[], int B[]) {
    n = N;
    for (int i=0; i<n; i++) {
        rng.eb(A[i], B[i]);
    }
    sort(ALL(rng));
    root[0] = build(1, n+1);
    for (int i=1, j=0, sz=0; i<=n; i++) {
        root[i] = root[i-1];
        while (j<n && rng[j].X == i) {
            cur[sz++] = rng[j++].Y;
        }
        if (sz) root[i] = ins(1, n+1, cur, sz, root[i]);
        sz = 0;
    }
}

struct Line {
    int i, l, r;
};
int *k, dp[MAXN];;
int tran (int f, int t) {
    debug(f, t);
    return dp[f] - k[t-1] + qry(root[f?k[f-1]:0], root[k[t-1]], k[t-1]);
}

int m;
int cut (int a, int b) {
    // max x s.t. f(a,x) < f(b,x)
    int L = max(a,b), R = m + 1;
    while (L < R - 1) {
        int M = (L + R) >> 1;
        if (tran(a,M) < tran(b,M)) L = M;
        else R = M;
    }
    return L;
}

int can(int M, int K[]) {
    m = M;
    sort(K, K+M);
    k = K;
    dp[0] = 0;

    deque<Line> deq;
    deq.pb({0, 1, M});
    for (int i=1; i<=M; i++) {
        // query
        while (deq.back().r < i) deq.pop_back();
        assert(deq.size());
        dp[i] = tran(deq.back().i, i);
#ifdef tmd
        int chk = tran(0, i);
        for (int j=1; j<i; j++) chk=min(chk, tran(j,i));
        assert(chk == dp[i]);
#endif

        while(deq.size() && tran(i, deq.back().r) < tran(deq.back().i, deq.back().r)) deq.pop_back();
        Line nw = Line{i, i+1, M};
        if (deq.size()) {
            int c = cut(i, deq.back().i);
            deq.back().l = c + 1;
            nw.r = c;
        }
        if (nw.r >= i+1) deq.push_back(nw);
    }
    pary(dp, dp+M+1);
    if (*min_element(dp, dp+M+1) < 0) return 0;
	else return 1;
}
