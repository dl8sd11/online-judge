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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int h, w, n, a;
int ans[102][102];

void chg (int id, int cl) {
    int r = id / w;
    int c = (r&1) ? w - id%w -1: id % w;
    ans[r][c] = cl;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> h >> w >> n;

    int idx = 0;
    REP1 (i, n) {
        cin >> a;
        REP (j, a) {
            chg(idx++, i);
        }
    }

    REP (i, h) {
        REP (j, w) {
            cout << ans[i][j] << " \n"[j==w-1];
        }
    }


    return 0;
}
