#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename IT> ostream&  __printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg;it!=ed;it++) {
        cout << (it==bg?"":",") << *it;
    }
    os << "}";
    return os;
}
template<typename T> ostream& operator << (ostream &os, vector<T> &vec) {
    return __printRng(os, vec.begin(), vec.end());
}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1003;
const int MAXM = 202;

int m;
ll dis[MAXM][MAXM];
ll dp[2][MAXM][MAXM];

vector<int> req;

void MN (ll &x, ll y) {
    x = min(x, y);
}
/*********Good***Luck*********/
int main () {
    IOS();

    cin >> m;
    cin.ignore();
    REP1 (i, m) {
        REP1 (j, m) {
            cin >> dis[i][j];
            cin.ignore();
        }
    }

    req.emplace_back(1);
    {
        string lne;
        int d;
        getline(cin, lne);
        stringstream ss;
        ss << lne;
        while (ss >> d) {
            req.emplace_back(d);
        }
        debug(req);
    }

    memset(dp, INF, sizeof(dp));
    dp[0][2][3] = 0;
    int n = SZ(req);

    ll ans = INF;
    REP1 (i, n-1) {
        REP (x, m+1) {
            REP (y, m+1) {
                dp[i&1][x][y] = INF;
            }
        }

        REP (x, m+1) {
            REP (y, m+1) {
                if (dp[(i&1)^1][x][y] != INF) {
                    int z = req[i-1];
                    int t = req[i];

                    MN(dp[i&1][x][y], dp[(i&1)^1][x][y] + dis[z][t]);
                    MN(dp[i&1][y][z], dp[(i&1)^1][x][y] + dis[x][t]);
                    MN(dp[i&1][x][z], dp[(i&1)^1][x][y] + dis[y][t]);
                }
            }
        }
//        debug(dp[i&1][0][0]);
//        debug(dp[i&1][1][0]);
//        debug(dp[i&1][0][1]);
//        debug(dp[i&1][4][2], dis[1][3]);

        if (i == n-1) {
            REP (x, m+1) {
                REP (y, m+1) {
//                    debug(x, y, dp[i&1][x][y]);
                    ans = min(ans, dp[i&1][x][y]);
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}

