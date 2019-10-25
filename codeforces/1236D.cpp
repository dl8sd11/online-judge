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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, m, k;
ll cnt;

vector<int> r[MAXN], c[MAXN];
int xr, xc, nr, nc;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> k;
    REP (i, k) {
        int x, y;
        cin >> x >> y;
        r[x].emplace_back(y);
        c[y].emplace_back(x);
    }

    REP1 (i, n) {
        r[i].emplace_back(0);
        r[i].emplace_back(m+1);
        sort(r[i].begin(), r[i].end());
    }
    REP1 (i, m) {
        c[i].emplace_back(0);
        c[i].emplace_back(n+1);
        sort(c[i].begin(), c[i].end());
    }

    xc = m+1, xr = n+1;
    int px = 1, py = 1;
    while (true) {
        debug(px, py);
        { // right
            auto ptr = lower_bound(r[px].begin(), r[px].end(), py);
            int edg = min(xc-1, (*ptr) - 1);
            debug(edg);
            if (edg == py && !(px == 1 && py == 1)) {
                break;
            } else {
                cnt += edg - py;
                py = edg;
            }
            nr = px;
        }

        debug(px, py);
        { // down
            auto ptr = lower_bound(c[py].begin(), c[py].end(), px);
            int edg = min(xr-1, (*ptr)-1);
            if (edg == px) {
                break;
            } else {
                cnt += edg - px;
                px = edg;
            }
            xc = py;
        }

        debug(px, py);
        { // left
            auto ptr = lower_bound(r[px].begin(), r[px].end(), py);
            ptr--;
            int edg = max(nc+1, (*ptr) + 1);
            if (edg == py) {
                break;
            } else {
                cnt += py - edg;
                py = edg;
            }
            xr = px;
        }

        debug(px, py);
        { // up
            auto ptr = lower_bound(c[py].begin(), c[py].end(), px);
            ptr--;
            int edg = max(nr+1, (*ptr)+1);
            debug(edg, *ptr);
            if (edg == px) {
                break;
            } else {
                cnt += px - edg;
                px = edg;
            }
            nc = py;
        }

    }

    cout << (cnt + 1 + k == 1LL*n*m ? "Yes" : "No") << endl;
}
