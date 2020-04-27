#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
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
// const ll MAXN =

int n, m, k;
vector<vector<int> > a;

typedef array<int,8> state;
map<state, int> dp[2];

void add (int &x, int y) {
    x = x + y >= MOD ? x + y - MOD : x + y;
}

int main () {
    TIME(main);
    IOS();

    cin >> n >> m >> k;

    a.resize(n, vector<int>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> a[i][j];
        }
    }

    if (n + m - 1 > k) {
        cout << 0 << endl;
    }

    if (n > m) {
        vector<vector<int> > nw(m, vector<int>(n));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                nw[j][i] = a[i][j];
            }
        }
        a = nw;
        swap(n, m);
    }

    state init = {};
    for (int i=0; i<10; i++) {
        init[i] = n;
    }

    bool c = 0;
    dp[c][init] = 1;

    for (int j=0; j<m; j++) {
        for (int i=0; i<n; i++) {
            debug(i ,j, dp[c].size());
            c ^= 1;
            dp[c].clear();
            for (auto st : dp[c^1]) {
                for (int x=0; x<k; x++) {
                    state rr = st.X;
                    if (a[i][j] == 0 || a[i][j]-1 == x) {
                        if (i < rr[x]) {
                            rr[x] = i;
                            add(dp[c][rr], st.Y);
                        }
                    }
                }
            }
        }    
    }

    int ans = 0;
    for (auto st : dp[c]) {
        ans += st.Y;
    }

    cout << ans << endl;
    return 0;
} 
