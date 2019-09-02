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

const ll MOD = 998244353;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 19;
const ll MAXS = 1<<10;

ll dp[2][MAXN][MAXS];
ll dp2[2][MAXN][MAXS];
ll num[MAXN];
ll ten[MAXN];

ll reg (ll x) {
    x %= MOD;
    return x < 0 ? x + MOD : x;
}

pll solve (int st, int idx, int state, bool les) {
    pll ret;
    if (idx < 0) {
        return {state == 0, 0};
    }
    if (dp[les][idx][state] != -1) {
        return {dp[les][idx][state], dp2[les][idx][state]};
    } else {
        dp[les][idx][state] = 0;
        dp2[les][idx][state] = 0;
    }
    REP (c, 10) {
        if (c == 0 && st == idx) {
            continue;
        }
        if (((state>>c)&1) && (!les || c <= num[idx])) {
            pll r1 = solve(st, idx-1, state, les && c == num[idx]);
            pll r2 = solve(st, idx-1, state^(1<<c), les && c == num[idx]);
            ret.X = reg(ret.X + r1.X + r2.X);
            ret.Y = reg(ret.Y + c * ten[idx] % MOD * (r1.X + r2.X));
            ret.Y = reg(ret.Y + r1.Y + r2.Y);
        }
    }
    dp[les][idx][state] = ret.X;
    dp2[les][idx][state] = ret.Y;
    return ret;
}

ll calc (ll bd, ll cl) {
    ll ret = 0;
    int len = 0;

    MEM(num, 0);
    REP (i, MAXN) {
        num[i] = bd % 10;
        bd /= 10;
        if (num[i]) {
            len = i;
        }
    }

    debug(len);
    REP (l, len + 1) {
        MEM(dp, -1);
        MEM(dp2, 0);
        REP (i, MAXS) {
            int cnt = 0;
            REP (j, 10) {
                cnt += (i>>j) & 1;
            }
            if (cnt <= cl) {
                pll r = solve(l, l, i, l == len);
                ret = reg(ret + r.Y);
            }
        }
    }

    return ret;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    ten[0] = 1;
    for (int i=1; i<=18; i++) {
        ten[i] = ten[i-1] * 10;
    }
    ll l, r, c;
    cin >> l >> r >> c;

    cout << reg(calc(r, c) - calc(l-1, c)) << endl;

    return 0;
}
