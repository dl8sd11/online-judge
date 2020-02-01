#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cmath>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define MEM(i,n) memset(i,n,sizeof i)
#define X first
#define Y second
#define SZ(_a) (int)_a.size()
#define ALL(_a) _a.begin(),_a.end()
#define pb push_back
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif


const ll MAXN=15,MAXlg=__lg(MAXN)+2;
const ll MOD=1000000007;
const ll INF=ll(1e18+7);

ll n,m;
ll dp[MAXN][MAXN][1<<MAXN];
int main()
{
    while (scanf("%d%d",&n,&m)) {
        if (n==0 && m==0) {
            break;
        }


        MEM(dp,0);
        dp[0][m][0] = 1;
        REP1 (i,n) {
            for (ll st=0;st<(1<<m);st++) {
                dp[i][0][st<<1] = dp[i-1][m][st];
            }
            REP1 (j,m) {
                ll down = 1 << j - 1;
                ll right = 1 << j;
                for (ll st=0;st<(1<<m+1);st++) {
                    if (!(st&down) && !(st&right)) {
                        dp[i][j][st] = dp[i][j-1][st+down] + dp[i][j-1][st+right];
                    } else if ((st&down) && (st&right)) {
                        dp[i][j][st] = 0;
                    } else if (st & down) {
                        dp[i][j][st] = dp[i][j-1][st-down];
                    } else if (st & right) {
                        dp[i][j][st] = dp[i][j-1][st-right];

                    }
                }
            }
        }

        printf("%d\n",dp[n][m][0]);
    }
}
