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
const ll MAXN = 2e5 + 5;

int r, c, q;
vector<string> g;

struct ZKW {
    int N;
    vector<int> seg;
    ZKW(){}
    ZKW (const vector<int> &v) {
        N = SZ(v);
        seg.resize(N * 2);
        for (int i=0; i<N; i++) seg[i+N] = v[i];
        for (int i=N-1; i>0; i--) seg[i] = min(seg[i<<1], seg[i<<1|1]);
    }
    int qry (int L, int R) {
        int res = 0x3f3f3f3f;
        for (L+=N, R+=N; L<R; L>>=1, R>>=1) {
            if (L&1) res = min(res, seg[L++]);
            if (R&1) res = min(res, seg[--R]);
        }
        return res;
    }
};

struct SuffixArray {
    string s;
    int N;
    vector<int> sa, rk, t, hei;
    ZKW lcp;

    SuffixArray (string _s) : s(_s), N(SZ(s)), sa(N), rk(N), t(N), hei(N) {
        iota(ALL(sa), 0);
        for (int i=0; i<N; i++) rk[i] = s[i];
        for (int h=1; ; h<<=1) {
            auto cmp = [&](int i, int j) {
                if (rk[i] != rk[j]) return rk[i] < rk[j];
                else return (i+h<N && j+h<N) ? rk[i+h] < rk[j+h] : i > j;
            };
            sort(ALL(sa), cmp);
            for (int i=1; i<N; i++) t[i] = t[i-1] + cmp(sa[i-1], sa[i]);
            for (int i=0; i<N; i++) rk[sa[i]] = t[i];
            if (rk[sa[N-1]] == N-1) break;
        }
        int clcp = 0;
        for (int i=0; i<N; i++) {
            clcp = max(clcp-1, 0);
            if (rk[i] == 0) clcp = hei[0] = 0;
            else {
                while (s[i+clcp] == s[sa[rk[i]-1]+clcp]) clcp++;
                hei[rk[i]] = clcp;
            }
        }
        lcp = ZKW(hei);
    }

    pii grng (int p, int len) {
        p = rk[p];

        pii res;
        {
            int L = -1, R = p;
            while (L < R - 1) {
                int M = (L + R) >> 1;
                if (lcp.qry(M+1, p+1) >= len) R = M;
                else L = M;
            }
            res.X = R;
        }
        {
            int L = p, R = N;
            while (L < R - 1) {
                int M = (L + R) >> 1;
                if (lcp.qry(p+1, M+1) >= len) L = M;
                else R = M;
            }
            res.Y = L;
        }
        return res;

    }
};

struct RSum_2D {
    int N;
    vector<vector<int> > bit;
    RSum_2D (int sz): N(sz+5), bit(sz + 5){}
    void add (int x, int y) {
        for (x++; x<N; x+=-x&x) {
            bit[x].eb(y);
        }
    }

    void build () {
        for (auto &v : bit) sort(ALL(v));
    }

    int pre(int x, pii y) {
        int res = 0;
        for (x++; x>0; x-=-x&x) {
            res += int(upper_bound(ALL(bit[x]), y.Y) - 
                   lower_bound(ALL(bit[x]), y.X));
        }
        return res;
    }

    int qry (pii x, pii y) {
        return pre(x.Y, y) - pre(x.X-1, y);
    }
};

signed main () {
    TIME(main);
    IOS();
    cin >> r >> c >> q;
    g.resize(r);
    for (int i=0; i<r; i++) {
        cin >> g[i];
    }

    string vs, hs;

    vector<vector<int> > vgp(r, vector<int>(c)), hgp(r, vector<int>(c));
    for (int i=0; i<r; i++) {
        for (int j=c-1; j>=0; j--) {
            hgp[i][j] = SZ(hs);
            hs += g[i][j];
        }
        hs += '@';
    }
    for (int j=0; j<c; j++) {
        for (int i=0; i<r; i++) {
            vgp[i][j] = SZ(vs);
            vs += g[i][j];
        }
        vs += '@';
    }

    vector<int> vpos(q), hpos(q);
    vector<string> qstr;
    for (int i=0; i<q; i++) {
        string str;
        cin >> str;
        qstr.eb(str);

        vpos[i] = SZ(vs);
        vs += str + '@';

        reverse(ALL(str));
        hpos[i] = SZ(hs);
        hs += str + '@';
    }

    SuffixArray vsa(vs), hsa(hs);
    RSum_2D sum(SZ(vs));
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            sum.add(vsa.rk[vgp[i][j]], hsa.rk[hgp[i][j]]);
        }
    }
    sum.build();

    debug(vs, vsa.sa);
    debug(hs, hsa.sa);
    for (int i=0; i<q; i++) {
        int sz = SZ(qstr[i]);
        int ans = 0;
        for (int j=1; j<=sz; j++) {
            pii xrng = vsa.grng(vpos[i]+j-1, SZ(qstr[i]) - j + 1);
            pii yrng = hsa.grng(hpos[i]+SZ(qstr[i])-j, j);
            int res = sum.qry(xrng, yrng);
            ans += res;
        }
        cout << ans << endl;
    }

    return 0;
}

