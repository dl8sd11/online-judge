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
const ll MAXN = 1003;

int n, m, k, a[MAXN][MAXN], msk[12][12], col[12];
void add (int &x, int y) {
    x = x + y >= MOD ? x + y - MOD : x + y;
}

int dfs (int x, int y) {
    if (y == m + 1) {
        x++;
        y = 1;
    }
    if (x == n + 1) {
        return 1;
    }

    int ans = 0, first = -1, cur = msk[x-1][y] | msk[x][y-1];

    if (k-__builtin_popcount(cur) < n+m-x-y+1) {
        return 0;
    }

    for (int i=0; i<k; i++) {
        if (((cur>>i)&1) == 0) {

            if (a[x][y] == -1 || a[x][y] == i) {
                msk[x][y] = cur | (1<<i);

                col[i]++;

                if (col[i] == 1) {
                    if (first == -1) {
                        first = dfs(x, y+1);
                        add(ans, first);
                    } else {
                        add(ans, first);
                    }
                } else {
                    add(ans, dfs(x, y+1));
                }


                col[i]--;

            }
        }
    }

    return ans;
}

int main () {
    TIME(main);
    IOS();

    cin >> n >> m >> k;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            cin >> a[i][j];
            if (--a[i][j] >= 0) {
                col[a[i][j]]++;
            }
        }
    }
    if (n+m-1 > k) {
        cout << 0 << endl;
        return 0;
    }

    cout << dfs(1,1) << endl;

    return 0;
}
