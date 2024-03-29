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

vector<pair<int,int> > pa;

void add (int f, int t) {
    // cout << f << " " << t << endl;
    pa.emplace_back(f, t);
}

/********** Good Luck :) **********/
int main( int argc, char** argv ){
    TIME(main);
    IOS();

    ll n;

    ll mx = 0;

    ll ans = 0;
    for (ll i=1;i<=1000;i++) {
        ll sz = (3+i)*i/2;
        if (((i+1)/2) * (1000-sz) >= mx) {
            ans = i;
            debug(i,sz);
        }
        mx = max(mx, ((i+1)/2) * (1000-sz));
    }


    vector<vector<int> > vec;
    int cnt = 0;

    int k = 25;
    const int MAXN = 999;
    int off = MAXN-(3+k)*k/2;
    REP1 (i, k) {
        vector<int> nw;
        REP1 (j, i+1) {
            nw.emplace_back(++cnt+off);
            if (j > 1) {
                add(nw[SZ(nw)-2],nw.back());
            }
        }
        vec.emplace_back(nw);
    }

    // debug(vec);

    int mid = 1;

    for (int i=2; i<=off; i++) {
        add(mid, i);
        for (int j=0; j<SZ(vec);j+=2) {
            add(i, vec[j][1]);
        }
    }
    // debug(pa);

    cout << MAXN << " " << SZ(pa) << endl;
    for (auto v : pa) {
        assert(v.X < v.Y);
        cout << v.X << " " << v.Y << endl;
    }

    debug(MAXN, SZ(pa));

    debug(mx);
    return 0;
}
