#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
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

const pll MOD = {1000000007, 1000000009};
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
// const ll MAXN = 

string s, t;


const pii aa = {880301, 20020607};

const int csz = 31;
pii pw[csz];

void build () {
    pw[0] = {1, 1};
    REP1 (i, csz-1) {
        pw[i].X = pw[i-1].X * aa.X % MOD.X;
        pw[i].Y = pw[i-1].Y * aa.Y % MOD.Y;
    }
    pary(pw, pw+3);
}

void add (pii &a, pii b) {
    (a.X += b.X) %= MOD.X;
    (a.Y += b.Y) %= MOD.Y;
}
void sub (pii &a, pii b) {
    (a.X -= b.X) %= MOD.X;
    (a.Y -= b.Y) %= MOD.Y;
    if (a.X < 0) {
        a.X += MOD.X;
    }
    if (a.Y < 0) {
        a.Y += MOD.Y;
    }
}
vector<pii> hs(const string &S, const int len) {
    vector<pii> ret;
    pii cur = {0, 0};
    REP (i, SZ(S)) {
        add(cur, pw[S[i]-'a']);
        if (i >= len-1) {
            ret.eb(cur);
            sub(cur,pw[S[i-len+1]-'a']);
        }
    }

    return ret;
}
bool check (int len) {
    if (len == 0) {
        return true;
    }
    vector<pii> sh = hs(s, len);
    vector<pii> th = hs(t, len);

    debug(sh);
    debug(th);

    sort(ALL(sh));
    for (auto v : th) {
        auto ptr = lower_bound(ALL(sh), v);
        if (ptr != sh.end() && *ptr == v) {
            return true;
        }
    }

    return false;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    build();

    cin >> s >> t;
    RREP (i, min(SZ(s), SZ(t))) {
        if (check(i)) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
