#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 21;
const ll MOD = 1000000007;

int n, m;
bool a[2][MAXN], b[2][MAXN];

int solve (int x) {
    int ans = 0;
    REP (i, n) {
        for (int j=i; j<= n; j++) {
            if (j == n) {
                return 10000000;
            }
            if (a[x][j] == b[x][i]) {
                debug(x, i, j);
                for (int k=j; k>i; k--) {
                    debug(x, k);
                    swap(a[x][k], a[x][k-1]);
                    ans++;
                }
                break;
            }
        }
    }
    return ans;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        cin >> a[0][i];
        a[1][i] = a[0][i];
    }

    int idx = 0;
    REP (i, m) {
        int d;
        cin >> d;
        REP (j, d) {
            b[0][idx] = i&1;
            b[1][idx] = (i&1)^1;
            idx++;
        }
    }
    REP (i, n) {
        debug(a[0][i], b[0][i], b[1][i]);
    }

    cout << min(solve(0), solve(1)) << endl;
    return 0;
}
