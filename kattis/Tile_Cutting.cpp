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
const ll MAXN = 1<<20;
const int MAXC = 500005;
typedef complex<double> cd;
const double pi = acos(-1);
int t;
cd a[MAXN], b[MAXN], c[MAXN], omg[MAXN+1];

void FFT (cd *v, int d) {
    for (int i=1,j=MAXN>>1; i<MAXN-1; i++) {
        if (i < j) {
            swap(v[i], v[j]);
        }
        int k = MAXN>>1;
        while (k <= j) {
            j -= k;
            k >>= 1;
        }
        if (k > j) {
            j += k;
        }
    }

    for (int h=2; h<=MAXN; h<<=1) {
        for (int i=0; i<MAXN; i+=h) {
            for (int k=i; k<i+h/2; k++) {
                int idx = k-i;
                int r = k+h/2;
                cd x = v[k] - omg[d > 0 ? idx*(MAXN/h) : MAXN-idx*(MAXN/h)] * v[r];
                v[k] = v[k] + omg[d > 0 ? idx*(MAXN/h) : MAXN-idx*(MAXN/h)] * v[r];
                v[r] = x;
            }
        }
    }

    if (d < 0) {
        REP (i, MAXN) {
            c[i] /= MAXN;
        }
    }
}

void build_omg() {
    omg[0] = omg[MAXN] = 1;
    REP1 (i, MAXN-1) {
        omg[i] = polar(1.0, i*pi*2/MAXN);
    }
}

int cnt[MAXC];
ll ans[MAXC];

void solve () {
    build_omg();
    for (int i=1; i<MAXC; i++) {
        for (int j=i; j<MAXC; j+=i) {
            cnt[j]++;
        }
    }

    REP (i, MAXC) {
        a[i] = cnt[i];
        b[i] = cnt[i];
    }

    FFT(a, 1);
    FFT(b, 1);
    REP (i, MAXN) {
        c[i] = a[i] * b[i];
    }
    FFT(c, -1);

    REP (i, MAXC) {
        ans[i] = round(c[i].real());
    }

}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    solve();
    cin >> t;

    while (t--) {
        int l, r;
        cin >> l >> r;
        int bst = l;
        debug(l, r);
        for (int i=l; i<=r; i++) {
            if (ans[i] > ans[bst]) {
                bst = i;
            }
        }

        cout << bst << " " << ans[bst] << endl;
    }
    return 0;
}
