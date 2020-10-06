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

struct SuffixArray {
    string s;
    int N;
    vector<int> sa, rk, t, hei;
 
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
    }
};

struct Data {
    int lcp, L, R;
};
signed main () {
    TIME(main);
    IOS();

#ifndef tmd
    freopen("blackboard.in", "r", stdin);
    freopen("blackboard.out", "w", stdout);
#endif

    string a, b, c;
    cin >> a >> b;
    c = a + "2" + b;
    SuffixArray sa(c);

    int ans = SZ(a);
    /*
     2N - 2LCP
    l=> +SA -P +N
    r=> -SA +P -N

    L=> -2lcp 

     */
    int N = SZ(a);
    debug(c);
    debug(sa.sa);
    debug(sa.hei);
    for (int _=0; _<2; _++) {
        vector<Data> stk;
        multiset<int> bst[2];
        for (int i=1; i<SZ(c); i++) {
            int lmn = iNF, rmn = iNF;

            while (stk.size() && stk.back().lcp >= sa.hei[i]) {
                bst[0].erase(bst[0].find(-2*stk.back().lcp+stk.back().L));
                lmn = min(lmn, stk.back().L);
                bst[1].erase(bst[1].find(-2*stk.back().lcp+stk.back().R));
                rmn = min(rmn, stk.back().R);
                stk.pop_back();
            }

            if (sa.sa[i-1] > SZ(a)) {
                lmn = min(lmn, -sa.sa[i-1]+1);
                rmn = min(rmn, sa.sa[i-1]-1);
            }
            debug(i, lmn, rmn);

            stk.pb({sa.hei[i], lmn, rmn});
            bst[0].insert(-2*stk.back().lcp+stk.back().L);
            bst[1].insert(-2*stk.back().lcp+stk.back().R);
            if (stk.size() && sa.sa[i] < SZ(a)) {
                ans = min({ans, sa.sa[i] + *bst[0].begin() + 3*N, *bst[1].begin() + N - sa.sa[i]});
            }
        }

        c = b + "2" + a;
        sa = SuffixArray(c);
    }

    cout << ans << endl;
    return 0;
}

