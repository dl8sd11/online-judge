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

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const int MAXN = 4096;

int n,k;
int u[MAXN][MAXN];
int pre[MAXN][MAXN];
int dp[MAXN][1024];

inline int cost (int f,int t) {
    return pre[t][t] - pre[t][f-1] - pre[f-1][t] + pre[f-1][f-1];;
}

int trans(int i,int d,int oL,int oR) {
    int mn = oL;
    int val = dp[mn][d-1]+cost(mn+1,i);
    for (int t=oL;t<=oR;t++) {
        if (val > dp[t][d-1]+cost(t+1,i)) {
            mn = t;
            val = dp[mn][d-1]+cost(mn+1,i);
        }
    }
    dp[i][d] = val;
    return mn;
}
void solve(int d,int L,int R,int oL,int oR) {
    if (L == R) {
        trans(L,d,oL,oR);
    } else if (L < R) {
        int M = (L + R) >> 1;
        int o = trans(M,d,oL,oR);
        solve(d,L,M-1,oL,o);
        solve(d,M+1,R,o,oR);
    }
}

char s[10000];
/********** Good Luck :) **********/
int main()
{
    // IOS();
    // cin >> n >> k;
    gets(s);
    sscanf(s,"%d %d",&n,&k);
    REP1 (i,n) {
        gets(s);
        debug(s);
        REP1 (j,n) {
            u[i][j] = s[(j-1)*2]-'0';
            if (i < j) {
                u[i][j] = 0;
            }
            pre[i][j] = u[i][j] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }
    }

    MEM(dp,INF);
    dp[0][0] = 0;

    REP1 (i,n) {
        dp[i][1] = cost(1,i);
    }

    for (int i=2;i<=k;i++) {
        solve(i,1,n,1,n);
    }

    printf("%d\n",dp[n][k]);
    return 0;
}
