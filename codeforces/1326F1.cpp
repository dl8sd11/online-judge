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

const int MAXN = 14;
const ll MOD = 1000000007;

vector<vector<vector<ll> > > dp;

bool g[MAXN][MAXN];
int n;

inline int low (int x) {
    return -x & x;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            char c;
            cin >> c;
            g[i][j] = c == '1';
        }
    }

    dp.resize(1<<n, vector<vector<ll> >(n, vector<ll>()));

    for (int mask=1; mask<(1<<n); mask++) {
        vector<int> id;
        for (int tmp=mask; tmp>0; tmp-=low(tmp)) {
            id.emplace_back(__lg(low(tmp)));
        }
        debug(mask, id);

        if (id.size() > 1) {

            for (int c : id) {
                int len = id.size() - 1;
                dp[mask][c].resize(1<<len, 0);

                for (int p : id) {
                    if (p == c) {
                        continue;
                    }

                    int add = g[c][p] << (len-1);
                    for (int i=0; i<(1<<(len-1)); i++) {
                        dp[mask][c][i|add] += dp[mask^(1<<c)][p][i];
                    }

                }
            }

        } else {
            dp[mask][id[0]].eb(1);
            debug(dp[mask][id[0]]);
        }

        debug(dp[mask][id[0]]);
    }

    vector<ll> ans(1<<n-1, 0);
    for (int i=0; i<n; i++) {
        for (int j=0; j<(1<<n-1); j++) {
            ans[j] += dp[(1<<n)-1][i][j];
        }
    }

    for (int i=0; i<(1<<n-1); i++) {
        if (i != 0) {
            cout << " ";
        }
        cout << ans[i];
    }

    cout << endl;
}

