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

const int MAXM = 20034;
const ll MOD = 1000000007;

int n, m, k, val[53][MAXM], dp[53][MAXM];

struct Min {
    int dt[MAXM];
    vector<pair<int,int> > rk;
    Min (int arr[]) {
        for (int i=0; i<m; i++) {
            dt[i] = arr[i];
            rk.eb(dt[i], i);
        }
        sort(ALL(rk));
    }

    void add (int x, int v) {
        dt[x] += v;
    }

    int qry () {
        int res = 0;
        for (int i=0; i<min(SZ(rk), k*2); i++) {
            res = max(res, dt[rk[SZ(rk)-i-1].Y]);
        }
        return res;
    }
};
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> k;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> val[i][j];
        }
    }

    for (int j=0; j<m; j++) {
        for (int l=0; l<k; l++) {
            dp[0][j] += val[0][l+j] + val[1][l+j];
        }
    }
    pary(dp[0], dp[0]+m);

    for (int i=1; i<n; i++) {
        Min bst(dp[i-1]);
        for (int j=0; j<m; j++) {
            int sum = 0;
            for (int p=j-k+1; p<j+k; p++) {
                if (p <= j) {
                    sum += val[i][p+k-1];
                } else {
                    sum -= val[i][p-1];
                }
                if (p >= 0 && p < m) {
                    bst.add(p, -sum);
                }
            }

            dp[i][j] = bst.qry();
            for (int p=0; p<k; p++) {
                dp[i][j] += val[i][j+p] + val[i+1][j+p];
            }

            sum = 0;
            for (int p=j-k+1; p<j+k; p++) {
                if (p <= j) {
                    sum += val[i][p+k-1];
                } else {
                    sum -= val[i][p-1];
                }
                if (p >= 0 && p < m) {
                    bst.add(p, sum);
                }
            }
        }
        pary(dp[i], dp[i]+m);
    }

    int ans = 0;
    for (int j=0; j<m; j++) {
        ans = max(ans, dp[n-1][j]);
    }
    cout << ans << endl;


}

