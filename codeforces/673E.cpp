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
const ll MAXN = 200005;

/*
    dp[i][j] = dp[i-1][j] + cost(j+1, i)
    sum(l, r) = sum(p[i] - p[l]) / a[i]
 */
int n, k, t[MAXN];
ll p[MAXN];
double dp[51][MAXN], tp[MAXN], ip[MAXN];

double cost(int l, int r) {
    return (tp[r] - tp[l-1]) - (ip[r] - ip[l-1]) * p[l-1];
}

void solve(int i, int jL, int jR, int tL, int tR) {
    if (jL >= jR) {
        return;
    }
    if (tL == tR - 1) {
        for (int j=jL;j < jR;j++) {
            dp[i][j] = dp[i-1][tL] + cost(tR, j);
        }
    } else {
        int jM = (jL + jR) >> 1;
        int bst = tL;
        dp[i][jM] = 1e18;
        for (int tr=tL; tr < min(tR, jM); tr++) {
            double cur = dp[i-1][tr] + cost(tr+1, jM);
            if (dp[i][jM] > cur) {
                dp[i][jM] = cur;
                bst = tr;
            }
        }

        solve(i, jL, jM, tL, bst+1);
        solve(i, jM+1, jR, bst, tR);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    REP1 (i, n) {
        cin >> t[i];
        p[i] = p[i-1] + t[i];
        tp[i] = p[i] * 1.0 / t[i] + tp[i-1];
        ip[i] = 1.0 / t[i] + ip[i-1];
    }

    double sum = 0;
    REP1 (i, n) {
        sum += 1.0 * p[i] / t[i];
        dp[1][i] = sum;
    }

    for (int i=2;i<=k;i++) {
        dp[i][0] = 0;
        solve(i, 1, n+1, 0, n+1);
    }
    debug(dp[1][1]);
    debug(dp[2][4]);

    cout << fixed << setprecision(20) << dp[k][n] << endl;
    return 0;
}
