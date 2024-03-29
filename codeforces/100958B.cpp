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
#ifdef tmdd
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

vector<string> vs;

ll dp[51][51][26][26][20];
int n;
ll solve (int l, int r, int li, int ri, int f) {
    if (dp[l][r][li][ri][f] != -1) {
        return dp[l][r][li][ri][f];

    }
    if (f == SZ(vs[0])-1 && l == r - 1) return 1;
    if (li == ri) {
        ll res = 0;
        for (int i=0; i<26; i++) {
            for (int j=0; j<26; j++) {
                if (vs[l][f+1]!='?' && vs[l][f+1]-'a'!=i) {
                    continue;
                }
                if (vs[r-1][f+1]!='?' && vs[r-1][f+1]-'a'!=j) {
                    continue;
                }
                res += solve(l, r, i, j, f+1);
                res %= MOD;
            }
        }
        dp[l][r][li][ri][f] = res;
        debug(l, r, li, ri, f, res);
        return res;
    }
    int lst = l;
    for (int i=l+1; i<r-1; i++) {
        if (vs[i][f]-'a' == li) {
            lst = i;
        }
    }
    int fst = r-1;
    for (int i=r-2; i>=l; i--) {
        if (vs[i][f] != '?' && vs[i][f]-'a' > li) {
            fst = i;
        }
    }
    int lin = (fst == r-1 ? ri : vs[fst][f]-'a');

    ll res = 0;
    for (int i=lst; i<fst; i++) {
        for (int j=li+1; j<=lin; j++) {
            res += solve(l, i+1, li, li, f) * solve(i+1, r, j, ri, f);
            res %= MOD;
        }
    }

    debug(l, r, li, ri, f, res);
    dp[l][r][li][ri][f] = res;
    return res;

}

signed main () {
    TIME(main);
    IOS();

    cin >> n;
    memset(dp, -1, sizeof(dp));

    int mx = 0;
    for (int i=0; i<n; i++) {
        string str;
#ifdef tmd
        str = "????????????????????";
#else
        cin >> str;

#endif
        vs.eb(str);
        mx = max(mx, SZ(str));
    }

    for (int i=0; i<n; i++) {
        while (SZ(vs[i]) < mx+1) {
            vs[i] += char('a');
        }
    }
    debug(vs);

    ll res = 0;
    for (int i=0; i<26; i++) {
        for (int j=0; j<26; j++) {
            if (vs[0][0]!='?' && vs[0][0]-'a'!=i) {
                continue;
            }
            if (vs[n-1][0]!='?' && vs[n-1][0]-'a'!=j) {
                continue;
            }
            res += solve(0, n, i, j, 0);
            res %= MOD;
        }
    }
    cout << res << endl;

    return 0;
}
/*
3
snuje
????e
snule
 */
