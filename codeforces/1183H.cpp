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
const ll INF = 1000000000012;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 102; 

ll n, k;
string str;
ll dp[MAXN][MAXN][26];
ll sum[MAXN][MAXN];
ll lst[26];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    cin >> str;
    REP (i,26) {
        dp[0][0][i] = 1;
    }
    sum[0][0] = 1;

    REP1 (i, n) {
        sum[i][0] = 1;
        REP1 (j,i) {
            REP (k, 26) {
                if (str[i-1] == ('a'+k)) {
                    if (sum[i-1][j-1] >= INF || dp[i-1][j][k] >= INF)  {
                        dp[i][j][k] = INF;
                    } else {
                        dp[i][j][k] = sum[i-1][j-1] - dp[lst[k]][j][k] + dp[i-1][j][k];
                    }
                } else {
                    dp[i][j][k] = dp[i-1][j][k];
                }
                sum[i][j] += (str[i-1] == ('a'+k) ? sum[i-1][j-1] - dp[lst[k]][j][k] : 0) + dp[i-1][j][k];
                if (sum[i][j] >= INF) {
                    sum[i][j] = INF;
                }
            }
        }
        lst[str[i-1]-'a'] = i;
    }

    ll ans = 0, cnt = 0;
    RREP (i, n) {
        ll dt = min(k - cnt, sum[n][i]);
        ans += (n - i) * dt;
        cnt += dt;
    }
    
    cout << (cnt == k ? ans : -1) << endl;
    return 0;
}
