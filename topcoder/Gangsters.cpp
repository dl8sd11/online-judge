#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 152;
class Gangsters {
public:
    ll dp[MAXN][MAXN], c[MAXN][MAXN];

    void norm(ll &x) {
        x %= MOD;
    }

    Gangsters() {
        MEM(dp, 0);
        c[0][0] = 1;
        REP1 (i, MAXN-1) {
            c[i][0] = 1;
            REP1 (j, i) {
                c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
            }
        }
    }

    int countOrderings(int people, int alive) {
        dp[0][1] = 1;
        dp[1][1] = 1;
        for (int i=2; i<=people-2; i++) {
            for (int j=1; j<=min(alive, i/2+1); j++) {
                dp[i][j] = dp[i-1][j];
                for (int k=0; k<i-1; k++) {
                    for (int l=0; l<=j; l++) {
                        norm(dp[i][j] += dp[k][l] * dp[i-k-2][j-l] % MOD * c[i-2][k] %MOD * (i-1) % MOD);
                    }
                }
            }
        }
        return dp[people-2][alive] * people * (people - 1) % MOD;
    }
};



/********** Good Luck :) **********/
int main()
{
    IOS();
    Gangsters gangster;
    int p, a;
    cin >> p >> a;
    cout << gangster.countOrderings(p, a) << endl;
    return 0;
}
