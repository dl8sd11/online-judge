#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
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
const int MAXN = 1<<20;
const ll MOD = 1000000007;
typedef complex<double> cd;

const double pi = acos(-1);
vector<int> bs;
cd omg[MAXN+3];

void FFT (vector<cd> &v, int d) {
    for (int i=1,j=SZ(v)>>1; i<SZ(v)-1; i++) {
        if (i < j) {
            swap(v[i], v[j]);
        }
        int k = SZ(v)>>1;
        while (k <= j) {
            j -= k;
            k >>= 1;
        }
        if (k > j) {
            j += k;
        }
    }

    for (int h=2; h<=SZ(v); h<<=1) {
        for (int i=0; i<SZ(v); i+=h) {
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
        REP (i, SZ(v)) {
            v[i] /= SZ(v);
        }
    }
}

void build_omg() {
    omg[0] = omg[MAXN] = 1;
    REP1 (i, MAXN-1) {
        omg[i] = polar(1.0, i*pi*2/MAXN);
    }
}

vector<int> mul (vector<int> &v1, vector<int> &v2) {
    int n = 1;
    while (n < SZ(v1) + SZ(v2)) {
        n <<= 1;
    }
    vector<cd> x(n), y(n);
    REP (i, SZ(v1)) {
        x[i] = v1[i];
    }
    REP (i, SZ(v2)) {
        y[i] = v2[i];
    }
    FFT(x, 1);
    FFT(y, 1);
    REP (i, n) {
        x[i] *= y[i];
    }
    FFT(x, -1);
    vector<int> ret(n);
    REP (i, n) {
        ret[i] = min(1, (int)round(x[i].real()));
    }
    while (SZ(ret)>1 && ret.back() == 0) {
        ret.pop_back();
    }
    return ret;
    
}
/*********************GoodLuck***********************/
int main () {
    TIME(MAIN);
    IOS();
    build_omg();
    int n, K, a;
    cin >> n >> K;

    bs.resize(1001);
    REP (i, n) {
        cin >> a;
        bs[a] = 1;
    }
    while (SZ(bs)>1 && bs.back() == 0) {
        bs.pop_back();
    }


    vector<int> ret = {1};
    while (K) {
        if (K & 1) {
            ret = mul(ret, bs);
        }
        bs = mul(bs, bs);
        K >>= 1;
    }

    bool fs = true;
    REP (i, SZ(ret)) {
        if (ret[i] == 1) {
            if (!fs) {
                cout << " " << i;
            } else {
                cout << i;
                fs = false;
            }
        }
    }
    cout << endl;
    return 0;
}