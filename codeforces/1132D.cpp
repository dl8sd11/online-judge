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
const ll MAXN = 200005;

int n, k;
ll a[MAXN], b[MAXN], add[MAXN], die[MAXN];
pll seg[MAXN * 2];
void build () {
    for (int i=n-1; i>0; i--) {
        seg[i] = min(seg[i<<1], seg[i<<1|1]);
    }
}

pll qry () {
    return seg[1];
}

void chg (int pos, ll val) {
    for (seg[pos+=n].X = val; pos>1; pos>>=1) {
        seg[pos>>1] = min(seg[pos], seg[pos^1]);
    }
}

bool solve (ll pw) {
    REP (i, n) {
        add[i] = 0;
        seg[i+n].X = a[i] / b[i] + 1;
        seg[i+n].Y = i;
    }
    build();

    REP (i, k-1) {
        int ps = qry().Y;
        add[ps] += pw;
        chg(ps, (a[ps] + add[ps]) / b[ps] + 1);
        if (qry().X <= i + 1) {
            return false;
        }
    }
    return true;
}
/********** Good Luck **********/
int main()
{
    TIME(main);
    IOS();

    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
    }
    REP (i, n) {
        cin >> b[i];
    }

    // bool ret = solve(5);
    // debug(ret);
    ll l = -1, r = 100000000000014;
    while (l < r - 1) {
        ll m = (l + r) >> 1;
        if (solve(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << (r == 100000000000014 ? -1 : r) << endl;

    return 0;
}
