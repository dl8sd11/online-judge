#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 21;
const ll MOD = 1000000007;
const int MAXM = 11;
const int MAXC = 31;

/*
Solution maintain these table

pre[n][mask][sum] = prob if n got mask with sum
    O(n^2*2^m*m) = 4e6
dp[sum][n][mask] = prob [1..n] used mask and all <= sum
    O(m*n^2*3^m) = 2e8
ans[i] = dp[i][n-1][11111]

*/
int n, m;
int p[3][MAXM][MAXN];
ll ans[MAXC];

ll dp[MAXN][1<<MAXM];
ll lw[MAXN][1<<MAXM][MAXC];
ll pre[MAXN][1<<MAXM][MAXC];

int mmsk;
void build () {
    mmsk = 1<<m;

    REP (i, n) {
        REP (j,mmsk) {
            lw[i][j][0] = 1;
            REP (u, n) {
                if (j & (1<<u)) {



                }
            }

        }
    }
}

void solve (int lim) {

}

ll sub (ll x, ll y) {
    return x - y < 0 ? x-y+MOD : x-y;
}

ll add (ll x, ll y) {
    return x + y >= MOD ? x+y-MOD : x+y;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (k, 3) {
        REP (i, m) {
            REP (j, n) {
                cin >> p[k][i][j];
            }
        }
    }

    build();
    REP1 (i, m*3) {
        solve(i);
    }

    ll sum = 0;
    REP1 (i, m*3) {
        sum  = add(sum, sub(ans[i],ans[i-1])*i%MOD);
    }

    cout << sum << endl;
}

