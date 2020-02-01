#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 102;

int n, xp[MAXN], yp[MAXN];
double edg[MAXN][MAXN], dl;
double lx[MAXN], ly[MAXN];
bool vx[MAXN], vy[MAXN];
const double eps = 1e-9;

bool dfs (int x) {
    vx[x] = true;
    for (int y=0; y<n; y++) {
        if (!vy[y] && abs(lx[x] + ly[y] - edg[x][y]) < eps) {
            vy[y] = true;
            if (yp[y] == -1 || dfs(yp[y])) {
                yp[y] = x;
                xp[x] = y;
                return true;
            }
        }
    }

    return false;
}
/****GOOD_LUCK****/
int main () {
    IOS();
    cin >> n;
    REP (i, n) {
        REP (j, n) {
            cin >> edg[i][j];
            edg[i][j] = log(edg[i][j]);
        }
    }


    for (int x=0; x<n; x++) {
        lx[x] = 0;
        for (int y=0; y<n; y++) {
            lx[x] = max(lx[x], edg[x][y]);
        }
    }

    memset(xp, -1, sizeof(xp));
    memset(yp, -1, sizeof(yp));
    REP (X, n) {
        int tk = 0;
        while (true) {
            memset(vx, 0, sizeof(vx));
            memset(vy, 0, sizeof(vy));
            if (dfs(X)) {
                break;
            } else {
                dl = 10;
                for (int x=0; x<n; x++) {
                    if (vx[x]) {
                        for (int y=0; y<n; y++) {
                            if (!vy[y]) {
                                dl = min(dl, lx[x]+ly[y]-edg[x][y]);
                            }
                        }
                    }
                }
                debug(dl);


                for (int i=0; i<n; i++) {
                    if (vx[i]) {
                        lx[i] -= dl;
                    }
                    if (vy[i]) {
                        ly[i] += dl;
                    }
                }
            }
        }

    }

    for (int i=0; i<n; i++) {
        cout << yp[i]+1 << " \n"[i==n-1];
    }
    return 0;
}
