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

const int MAXN = 1<<18;
const ll MOD = 1000000007;

int n, k;
int a[MAXN];
int dp[MAXN*2][4];
bool vis[MAXN*2][4];
bool fan[MAXN];

int solve (int nd, int msk, int nL, int nR) {
    if (vis[nd][msk]) {
        return dp[nd][msk];
    } else if (nL == nR - 2) {
        int cnt = fan[nL] + fan[nL + 1];
        vis[nd][msk] = true;
        if (cnt == 2) {
            if (msk == 3) {
                debug(nd, msk, nL, nR);
                return dp[nd][msk] = 1;
            } else {
                return dp[nd][msk] = -1;
            }
        } else if (cnt == 1) {
            if (msk == 1 || msk == 2) {
                debug(nd, msk, nL, nR);
                return dp[nd][msk] = 1;
            } else {
                return dp[nd][msk] = -1;
            }
        } else {
            if (msk) {
                return dp[nd][msk] = -1;
            } else {
                debug(nd, msk, nL, nR);
                return dp[nd][msk] = 0;
            }
        }
    } else {
        int nM = (nL + nR) >> 1;

        REP (m1, 4) {
            REP (m2, 4) {
                if ((m1|m2) == msk) {
                    int d1 = solve(nd<<1, m1, nL, nM);
                    int d2 = solve(nd<<1|1, m2, nM, nR);

                    if (d1 >= 0 && d2 >= 0) {
                        if (nd == 3 && msk == 3) {
                            debug(m1, m2, d1, d2);
                        }
                        dp[nd][msk] = max(dp[nd][msk],d1 + d2 + ((m1|m2)&1) + ((m1|m2)&2));
                    }
                }
            }
        }
        vis[nd][msk] = true;
        debug(nd, msk, nL, nR, dp[nd][msk]);
        return dp[nd][msk];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, k) {
        cin >> a[i];
        a[i]--;
        fan[a[i]] = true;
    }

    memset(dp, -1, sizeof(dp));

    int ans = 0;
    REP (i, 4) {
        ans = max(ans, solve(1, i, 0, 1<<n) + (i!=0));
    }

    cout << ans << endl;
}
