#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 10;


struct Matrix {
    ll dt[MAXN][MAXN];
    Matrix() {
        MEM(dt,0);
    }
    void operator = (const Matrix &m) {
        REP (i,MAXN) {
            REP (j,MAXN) {
                dt[i][j] = m.dt[i][j];
            }
        }
    }

    Matrix operator *(const Matrix &m) {
        Matrix ret;
        REP (i,MAXN) {
            REP (j,MAXN) {
                REP (k,MAXN) {
                    ret.dt[i][j] += dt[i][k] * m.dt[k][j];
                    ret.dt[i][j] %= MOD - 1;
                }
            }
        }
        return ret;
    }
};
Matrix mpow(Matrix base,ll ep) {
    if (ep == 1) {
        return base;
    }
    Matrix hf = mpow(base,ep>>1);
    return ep & 1 ? hf * hf * base : hf * hf;
}

ll numpow(ll base,ll ep) {
    if (ep == 0) {
        return 1;
    }
    ll hf = numpow(base,ep>>1);
    return ep & 1 ? hf * hf % MOD * base % MOD: hf * hf % MOD;
}
ll n,f1,f2,f3,c;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> f1 >> f2 >> f3 >> c;
    ll fn = 1;

    Matrix t;
    REP (r,3) {
        t.dt[r][0] = 1;
    }
    t.dt[0][1] = 1;
    t.dt[1][2] = 1;
    t = mpow(t,n-3);
    

    fn = numpow(f1,t.dt[2][0]) * fn % MOD;
    fn = numpow(f2,t.dt[1][0]) * fn % MOD;
    fn = numpow(f3,t.dt[0][0]) * fn % MOD;

    Matrix tc;
    REP (r,4) {
        tc.dt[r][0] = 1;
    }
    tc.dt[0][1] = 1;
    tc.dt[1][2] = 1;
    tc.dt[3][3] = 1;
    tc.dt[4][3] = 1;
    tc.dt[4][4] = 1;
    tc = mpow(tc,n-3);

    fn = numpow(c,tc.dt[3][0]*2+tc.dt[4][0]*2) * fn % MOD;

    cout << fn << endl;
    return 0;
}
