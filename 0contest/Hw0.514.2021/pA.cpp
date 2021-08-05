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
const ll MAXN = 302;

int n, m;
deque<int> a[MAXN][MAXN];
string b[MAXN][MAXN];
int sz[MAXN][MAXN];
int one[MAXN], zero[MAXN];

vector<string> ans;
void mv (int fi, int fj, int ti, int tj) {
    string str = to_string(fi+1) + " " + to_string(fj+1) + ' ' + to_string(ti+1) + " " + to_string(tj+1);
    ans.emplace_back(str);
    // debug(str);
    a[ti][tj].push_front(a[fi][fj].back());
    a[fi][fj].pop_back();

}

void dist (int col, int *cnt) {
    vector<int> pos, neg;
    for (int i=0; i<n; i++) {
        if (a[i][col].size() < cnt[i]) neg.push_back(i);
        else pos.push_back(i);
    }

    while (pos.size() && neg.size()) {
        while (pos.size() && a[pos.back()][col].size() == cnt[pos.back()]) pos.pop_back();
        while (neg.size() && a[neg.back()][col].size() == cnt[neg.back()]) neg.pop_back();
        if (pos.empty() || neg.empty()) break;
        mv(pos.back(), col, neg.back(), col);
    }
}

signed main () {
    TIME(main);
    IOS();

    cin >> n >> m;

    int tot = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            string str;
            cin >> str;
            for (char c : str) a[i][j].push_back(c - '0');
            sz[i][j] = str.size();
            tot += sz[i][j];
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> b[i][j];
            for (char c : b[i][j]) one[i] += c == '1';
            for (char c : b[i][j]) zero[i] += c == '0';
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<sz[i][0]; j++) {
            if (a[i][0].back()) mv(i, 0, i, m-1);
            else mv(i, 0, (i+1)%n, 0);
        }
        for (int j=0; j<sz[i][m-1]; j++) {
            if (a[i][m-1].back()) mv(i, m-1, (i+1)%n, m-1);
            else mv(i, m-1, i, 0);
        }
        for (int j=1; j<m-1; j++) {
            while (a[i][j].size()) {
                if (a[i][j].back()) mv(i, j, i, m-1);
                else mv(i, j, i, 0);
            }
        }
    }

    dist(0, zero);
    dist(m-1, one);

    for (int i=0; i<n; i++) {
        for (int j=1; j<m-1; j++) {
            reverse(ALL(b[i][j]));
            for (char c : b[i][j]) {
                if (c == '0') mv(i, 0, i, j);
                else mv(i, m-1, i, j);
            }
        }
    }    

    for (int i=0; i<n; i++) {
        int cntz = 0, cnto = 0;
        for (char c : b[i][0]) cntz += c == '0'; 
        for (char c : b[i][m-1]) cnto += c == '1'; 
        for (int j=0; j<cntz; j++) mv(i, 0, (i+1)%n, 0);
        for (int j=0; j<cnto; j++) mv(i, m-1, (i+1)%n, m-1);
    }
    debug("好了");

    for (int i=0; i<n; i++) {
        reverse(ALL(b[i][0]));
        reverse(ALL(b[i][m-1]));
        for (auto c : b[i][0]) {
            if (c == '0') mv((i+1)%n, 0, i, 0);
            else mv(i, m-1, i, 0);
        }
        for (auto c : b[i][m-1]) {
            if (c == '1') mv((i+1)%n, m-1, i, m-1);
            else mv(i, 0, i, m-1);
        }
    }

    cout << ans.size() << endl;
    assert(tot * 4 >= ans.size());
    for (auto line : ans) cout << line << endl;


    // for (int i=0; i<n; i++) pary(a[i], a[i]+m);
    return 0;
}
