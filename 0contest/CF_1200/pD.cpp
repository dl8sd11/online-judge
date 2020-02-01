#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 2003;

int n, k, base;
int ans[MAXN][MAXN];
bool bd[MAXN][MAXN], con[2][MAXN][MAXN];
vector<int> bpos[2][MAXN];

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> k;
    REP (i, n) {
        REP (j, n) {
            char c;
            cin >> c;
            bd[i][j] = c == 'B';
        }
    }

    REP (i, n) {
        bool wl = true;
        REP (j, n) {
            if (bd[i][j]) {
                wl = false;
                bpos[0][i].eb(j);
            }
        }
        base += wl;
    }

    REP (j, n) {
        bool wl = true;
        REP (i, n) {
            if (bd[i][j]) {
                wl = false;
                bpos[1][j].eb(i);
            }
        }
        base += wl;
    }

    REP (j, n-k+1) {
        int cur = 0;
        REP (i, n) {
            if (!bpos[0][i].empty()) {
                auto lwb = lower_bound(ALL(bpos[0][i]), j);
                auto upb = lower_bound(ALL(bpos[0][i]), j+k);
                con[0][i][j] = (lwb == bpos[0][i].begin() && upb == bpos[0][i].end());
            }
            cur += con[0][i][j];
            if (i >= k-1) {
                ans[i-k+1][j] = base + cur;
                cur -= con[0][i-k+1][j];
            }
        }
    }
    REP (i, n) {
        pary(ans[i], ans[i]+n);
    }

    REP (i, n-k+1) {
        int cur = 0;
        REP (j, n) {
            if (!bpos[1][j].empty()) {
                auto lwb = lower_bound(ALL(bpos[1][j]), i);
                auto upb = lower_bound(ALL(bpos[1][j]), i+k);
                con[1][i][j] = (lwb == bpos[1][j].begin() && upb == bpos[1][j].end());
            }
            cur += con[1][i][j];
            if (j >= k-1) {
                ans[i][j-k+1] += cur;
                cur -= con[1][i][j-k+1];
            }
        }
    }

    int opt = base;
    REP (i, n) {
        pary(ans[i], ans[i]+n);
        REP (j, n) {
            opt = max(opt, ans[i][j]);
        }
    }

    cout << opt << endl;
    return 0;
}
