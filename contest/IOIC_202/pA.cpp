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
const int MAXN = 200005;
const int MAXLG = __lg(MAXN) + 3;

int n, a[MAXN];
struct Segment_MX {
    int dt[MAXN*2];

    void build () {
        for (int i=n-1;i>0;i--) {
            dt[i] = max(dt[i<<1], dt[i<<1|1]);
        }
    }

    int qry (int l, int r) {
        int ret = -iNF;
        for (l+=n, r+=n;l<r; l>>=1, r>>=1) {
            if (l&1) {
                ret = max(ret, dt[l++]);
            }
            if (r&1) {
                ret = max(ret, dt[--r]);
            }
        }
        return ret;
    }
} r[MAXLG];

struct Segment_MN {
    int dt[MAXN*2];

    void build () {
        for (int i=n-1;i>0;i--) {
            dt[i] = min(dt[i<<1], dt[i<<1|1]);
        }
    }

    int qry (int l, int r) {
        int ret = iNF;
        for (l+=n, r+=n;l<r; l>>=1, r>>=1) {
            if (l&1) {
                ret = min(ret, dt[l++]);
            }
            if (r&1) {
                ret = min(ret, dt[--r]);
            }
        }
        return ret;
    }
} l[MAXLG];
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i];
        l[0].dt[i+n] = max(0,i-a[i]);
        r[0].dt[i+n] = min(n-1,i+a[i]);
    }
    l[0].build();
    r[0].build();

    REP1 (i, MAXLG-1) {
        REP (j, n) {
            int L = l[i-1].dt[j+n];
            int R = r[i-1].dt[j+n];

            r[i].dt[n+j] = r[i-1].qry(L, R+1);
            l[i].dt[n+j] = l[i-1].qry(L, R+1);
            #ifdef tmd
            if (i <= 3) {
                debug(i, j, L, R);
            }
            #endif
        }
        l[i].build();
        r[i].build();
    }


    int ans = 0;
    REP (i, n) {
        int L = i, R = i;
        int cnt = 0;
        for (int i=MAXLG-1;i>=0;i--) {
            int nL = l[i].qry(L,R+1);
            int nR = r[i].qry(L,R+1);

            if (nL != 0 || nR != n-1) {
                L = nL;
                R = nR;
                cnt += 1 << i;
            }
        }

        ans = max(ans, cnt);
        debug(i, cnt);
    }

    cout << ans+1 << endl;

    return 0;
}
