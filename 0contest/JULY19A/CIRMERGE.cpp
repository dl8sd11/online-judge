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
const ll MAXN = 402;

int T, n, a[MAXN], b[MAXN], tr[MAXN][MAXN];
ll p[MAXN],dp[MAXN][MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> T;
    while (T--) {
        cin >> n;
        REP1 (i, n) {
            cin >> a[i];
        }

        ll ans = INF;
        REP (sft, n) {
            REP1 (j,n) {
                b[j] = a[(sft+j > n) ? sft+j-n : sft+j];
                p[j] = b[j] + p[j-1];
            }
            REP1 (i, n) {
                dp[i][i] = 0;
                tr[i][i] = i;
            }

            for (int len=2;len<=n;len++) {
                for (int l=1;l+len-1<=n;l++) {
                    int r = l + len - 1;
                    dp[l][r] = INF;
                    for (int t=tr[l][r-1];t<=tr[l+1][r];t++) {
                        if (dp[l][t] + dp[t+1][r] < dp[l][r]) {
                            dp[l][r] = dp[l][t] + dp[t+1][r];
                            tr[l][r] = t;
                        }
                    }
                    dp[l][r] += p[r] - p[l-1];
                }
            }


            ans = min(ans, dp[1][n]);
        }

        cout << ans << endl;
    }
    return 0;
}
