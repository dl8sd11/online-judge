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

const int mc = 2;
const ll MOD[mc] = {1000000009, 20020607};
ll bs[mc] = {256, 256};
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 1000006;

int n;
string cur, nw;
array<ll, mc> pr[MAXN], hs[MAXN];
array<ll, mc> fac[MAXN], inv[MAXN];

ll mpow(ll base,ll ep, int mid) {
    ep = ep % (MOD[mid] - 1);
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD[mid];
        }
        base = base * base % MOD[mid];
        ep >>= 1;
    }
    return ret;
}

void mrg () {
    REP (j, mc) {
        REP1 (i, SZ(nw)) {
            hs[i][j] = (hs[i-1][j] + fac[i][j] * nw[i-1]) % MOD[j];
        }
    }


    int len=min(SZ(cur), SZ(nw));
    debug(len);
    for (; len >=0; len--) {
        array<ll, mc> ch;
        REP (j, mc) {
            ch[j] = (pr[SZ(cur)][j] - pr[SZ(cur) - len][j] + MOD[j]) % MOD[j];
            ch[j] = ch[j] * inv[SZ(cur)-len][j] % MOD[j];
        }
        debug(ch[0], ch[1], hs[len][0], hs[len][1]);

        if (ch == hs[len]) {
            break;
        }
    }
    debug(len);

    REP (i, SZ(nw) - len) {
        REP (j, mc) {
            pr[SZ(cur)+1][j] = (pr[SZ(cur)][j] + fac[SZ(cur)+1][j] * nw[i+len]) % MOD[j];
        }
        cur += nw[i+len];
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    REP (j, mc) {
        bs[j] += rng() % 1000;
    }
    fac[0][0] = 1;
    fac[0][1] = 1;
    inv[0][0] = 1;
    inv[0][1] = 1;
    REP1 (i, MAXN-1) {
        REP (j, mc) {
            fac[i][j] = fac[i-1][j] * bs[j] % MOD[j];
            inv[i][j] = mpow(fac[i][j], MOD[j]-2, j);
        }
    }

    cin >> n;
    REP (i, n) {
        cin >> nw;
        mrg();
        debug(cur);
    }

    cout << cur << endl;
    return 0;
}
