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

const ll INF = 2000000007;
const int iNF = 0x3f3f3f3f;
// const ll MAXN =

ll sum (ll f, ll t) {
    ll len = t-f+1;
    return ll(f+t)*len/2;
}

ll bs1 (ll L, ll R) {
    ll l = 0, r = INF;
    while (l < r - 1) {
        ll m = (l + r) >> 1;
        if (L - sum(1,m) <= R) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

void opt (ll T, ll L, ll R, bool rev) {
    if (rev) {
        swap(L, R);
    }
    cout << T << " " << L << " " << R << endl;
}


ll sum2 (ll f, ll t) {
    ll len = (t-f)/2 + 1;
    return (f+t)*len/2;
}

pll eval (ll L, ll R, ll st, ll len) {
    pll res;
    ll LL = len / 2;
    ll RR = len - LL;
    res.X = L - sum2(st+1,st-1+LL*2);
    res.Y = R - sum2(st, st+(RR-1)*2);
    return res;
}

ll bs2 (ll L, ll R, ll st) {
    // start at st and R first

    ll l = 0, r = INF;
    while (l < r - 1) {
        ll m = (l + r) >> 1;
        pll res = eval(L, R, st, m);
        if (res.X < 0 || res.Y < 0) {
            r = m;
        } else {
            l = m;
        }
    }
    return l;
}


void solve (ll L, ll R, int ts) {
    cout << "Case #" << ts << ": ";
    bool rev = false;
    if (L < R) {
        swap(L,R);
        rev = true;
    }

    debug(L, R);
    ll del = bs1(L, R);
    debug(del);
    if (L - sum(1,del) < 0) {
        L -= sum(1,del-1);
        opt(del-1, L, R, rev);
        return;
    }

    L -= sum(1, del);
    ll fnl = bs2(L, R, del+1);
    
    if (L == R) {
        rev = true;
    }

    pll res = eval(L, R, del+1, fnl);
    opt(del+fnl, res.X, res.Y, rev);
}

int main () {
    TIME(main);
    IOS();
    debug(sum(1,INF));

    int t;
    cin >> t;

    int tcnt = 0;
    while (t--) {
        ll l, r;
        cin >> l >> r;
        solve(l,r,++tcnt);
    }



    return 0;
}
