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
const ll MAXN = 1003; 

bool vis[MAXN];
int a[MAXN];
int cnt[MAXN];

struct Adj {
    int x, y;

    pii gen () const {
        return {max(cnt[a[x]], cnt[a[y]]),min(cnt[a[x]], cnt[a[y]])};
    }

    bool operator < (const Adj &oth) const {
        pii me = gen();
        pii ot = oth.gen();
        return me > ot;
    }
};
signed main () {
    TIME(main);
    IOS();

    int n, k;
    cin >> n >> k;
    for (int i=0; i<n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    } 

    vector<pii> ans;
    for (int i=0; i<n/2; i++) {
        vector<int> alv;
        for (int j=0; j<n; j++) {
            if (!vis[j]) alv.eb(j);
        }

        alv.eb(alv.front());
        vector<Adj> can;
        for (int j=1; j<SZ(alv); j++) {
            if (a[alv[j-1]] != a[alv[j]]) {
                can.pb({alv[j-1], alv[j]});
            }
        }
        sort(ALL(can));
        if (can.empty()) {
            cout << -1 << endl;
            return 0;
        } else {
            ans.eb(can[0].x, can[0].y);
            cnt[a[can[0].x]]--;
            cnt[a[can[0].y]]--;
            vis[can[0].x] = true;
            vis[can[0].y] = true;
        }
    }

    for (int i=0; i<n/2; i++) {
        cout << ans[i].X+1 << " " << ans[i].Y+1 << endl;
    }

    return 0;
}

