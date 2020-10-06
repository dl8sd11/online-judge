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
const ll MAXN = 402; 

char w[MAXN][MAXN];
char ans[MAXN][MAXN];
vector<int> ch[MAXN], cv[MAXN];
signed main () {
    TIME(main);

    freopen("japanese.in", "r", stdin);
    freopen("japanese.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            char c;
            cin >> c;
            w[i][j] = c == 'X';
        }
    }

    for (int i=0; i<n; i++) {
        int cnt = w[i][0];
        for (int j=1; j<=m; j++) {
            if (w[i][j-1] == 1 && w[i][j] == 0) {
                ch[i].eb(cnt);
                cnt = 0;
            }
            if (w[i][j]) {
                cnt++;
            }
        }
    }

    for (int j=0; j<m; j++) {
        int cnt = w[0][j];
        for (int i=1; i<=n; i++) {
            if (w[i-1][j] == 1 && w[i][j] == 0) {
                cv[j].eb(cnt);
                cnt = 0;
            }
            if (w[i][j]) {
                cnt++;
            }
        }
    }

    int mxh = 0, mxv = 0;
    for (int i=0; i<n; i++) {
        mxh = max(mxh, SZ(ch[i]));
    }
    for (int i=0; i<m; i++) {
        mxv = max(mxv, SZ(cv[i]));
    }


    for (int i=0; i<mxv+n; i++) {
        for (int j=0; j<mxh+m; j++) {
            ans[i][j] = '.';
    
        }
    }

    for (int i=0; i<mxv; i++) {
        for (int j=0; j<mxh; j++) {
            ans[i][j] = '*';
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<mxh; j++) {
            ans[i+mxv][mxh-1-j] = j < SZ(ch[i]) ? ch[i][SZ(ch[i])-1-j]+'0' : '_';
        }
    }

    for (int j=0; j<m; j++) {
        for (int i=0; i<mxv; i++) {
            ans[mxv-1-i][j+mxh] = i < SZ(cv[j]) ? cv[j][SZ(cv[j])-1-i]+'0' : '_';
        }
    }

    for (int i=0; i<mxv+n; i++) {
        for (int j=0; j<mxh+m; j++) {
            cout << ans[i][j]; 
        }
        cout << endl;
    }



    return 0;
}
