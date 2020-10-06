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

const int MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 102 + 5;

int sub (int x, int y) {
    x -= y;
    return x < 0 ? x + MOD : x;
}

int add (int x, int y) {
    x += y;
    return x >= MOD ? x - MOD : x;
}

int mul (int x, int y) {
    return ll(x) * y % MOD;
}

int mpow (int x, int y) {
    int res = 1;
    while (y) {
        if (y&1) res = mul(res, x); 
        y >>= 1;
        x = mul(x, x);
    }
    return res;
}

int mdiv (int x, int y) {
    return mul(x, mpow(y, MOD-2));
}

vector<string> path[MAXN][2];
vector<int> pai[MAXN][2];

vector<string> st;
int eid (int u, int v) {
    return u * SZ(st) + v;
}
int gau[MAXN][42*42];
signed main () {
    TIME(main);
    IOS();

    freopen("equality.in", "r", stdin);
    freopen("equality.out", "w", stdout);

    int n;
    cin >> n;
    cin.ignore();
    n++;

    for (int i=0; i<n; i++) {
        string line, tok;
        getline(cin, line);
        stringstream ss;
        ss << line;
        int id = 0;
        while (ss >> tok) {
            if (tok == "=" || tok == "?") {
                id++;
            } else {
                path[i][id].eb(tok);
                st.eb(tok);
            }
        }
    }
    sort(ALL(st));
    st.resize(unique(ALL(st))-st.begin());

    for (int i=0; i<n; i++) {
        for (int j=0; j<2; j++) {
            for (auto t : path[i][j]) {
                pai[i][j].eb(lower_bound(ALL(st), t)-st.begin());
            }
            debug(i, j, pai[i][j]);
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<2; j++) {
            for (int k=1; k<SZ(pai[i][j]); k++) {
                int &x = gau[i][eid(pai[i][j][k], pai[i][j][k-1])];
                x = add(x, j?MOD-1:1);
            }
        }
    }

    for (int i=0; i<n; i++) {
        pary(gau[i], gau[i]+SZ(st)*SZ(st));
    }

    int m = SZ(st)*SZ(st);

    /*
     * n*m
     */

    for (int i=0, ii = 0; ii<n-1 && i<m; i++) {
        debug(ii, i);
       if(gau[ii][i] == 0){
           int h = ii+1;
           for(; h < n && gau[h][i] == 0; h++);
           if(h == n-1)return cout << "DUNNO\n", 0;
           if(h == n) continue;
           swap(gau[ii], gau[h]);
       } 
       debug(ii, i);
       for(int j = ii+1; j < n; j++){
           int t = mdiv(gau[j][i], gau[ii][i]);
           for(int k = 0; k < m; k++)
               gau[j][k] = sub(gau[j][k], mul(gau[ii][k], t));
       }
       ii++;
    }
    debug("end");
    for (int i=0; i<n; i++) {
        pary(gau[i], gau[i]+m);
    }
    for(int i = 0; i < m; i++)if(gau[n-1][i])return cout << "DUNNO\n", 0;
    cout << "YES" << endl;


    return 0;
}
