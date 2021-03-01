#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double,double> pdd;
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

const ll MOD = 0xdefaced;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 5003;
const int C[2] = {20020607, 880301};

vector<pair<pii, int>> rep;
string str;
int n, a, b, dp[MAXN];
ll hpre[2][MAXN], inv[2][MAXN];
bool tabl[MAXN][MAXN];

ll mpow(ll base,ll ep) {
    ep = ep % (MOD - 1);
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD;
        }
        base = base * base % MOD;
        ep >>= 1;
    }
    return ret;
}

int hh(int l, int r, int id) {
    return (hpre[id][r] - hpre[id][l-1] + MOD) * inv[id][l] % MOD;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> a >> b;
    cin >> str;
    inv[0][0] = 1;
    inv[1][0] = 1;
    REP (j, 2) {
        REP1 (i, n) {
            inv[j][i] = inv[j][i-1] * mpow(C[j], MOD-2) % MOD;
        }
    }

    REP (j, 2) {
        ll hs = 0, r = C[j];
        REP1 (i, n) {
            hs = (hs + r * int(str[i-1])) % MOD;
            hpre[j][i] = hs;
            r = r * C[j] % MOD;
        }
    }

    reverse(ALL(rep));
    REP1 (i,n) {
        rep.clear();
        for (int j=1; j+i-1<=n; j++) {
            rep.eb(pii(hh(j,j+i-1,0),hh(j,j+i-1,1)),j+i-1);
        }
        sort(ALL(rep));

        for (int j=1; j+i-1<=n; j++) {
            auto ptr = lower_bound(ALL(rep),pair<pii,int>(pii(hh(j,j+i-1,0),hh(j,j+i-1,1)),j));
            if (ptr != rep.begin() && prev(ptr)->X == pii(hh(j,j+i-1,0),hh(j,j+i-1,1))) {
                tabl[j][j+i-1] = true;
            }
        }
    }
    
    MEM(dp, iNF);
    dp[0] = 0;
    for (int i=1; i<=n; i++) {
        dp[i] = dp[i-1] + a;
        for (int t=0; t<i; t++) {
            if (tabl[t+1][i] && dp[t] + b < dp[i]) {
                dp[i] = dp[t] + b;
                debug(i, t);
            }
        }
    }
    cout << dp[n] << endl;
    return 0;
}
