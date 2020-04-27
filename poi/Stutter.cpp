#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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

const int MAXN = 15004;
const ll MOD = 1000000007;

int n, m, a[MAXN], b[MAXN], dp[2][MAXN], mem[MAXN], lb[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        cin >> a[i];
    }
    for (int i=1; i<=m; i++) {
        cin >> b[i];
    }

    map<int,int> lstb;
    for (int i=1; i<=m; i++) {
        lb[i] = lstb[b[i]];
        lstb[b[i]] = i;

        mem[i] = -MOD;
    }
    mem[0] = -MOD;


    for (int i=1; i<=n; i++) {

        for (int j=1; j<=m; j++) {

            dp[i&1][j] = max(dp[i&1^1][j], dp[i&1][j-1]);

            if (a[i] == b[j]) {
                dp[i&1][j] = max(dp[i&1][j], mem[lb[j]]+1);

                if (lb[j] > 0) {
                    mem[lb[j]] = dp[i&1^1][lb[j]-1];
                }
            }
        }

        debug(i);
        pary(dp[i&1], dp[i&1]+m+1);
    }

    cout << dp[n&1][m] * 2<< endl;


}

