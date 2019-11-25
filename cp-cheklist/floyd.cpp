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

const int MAXN = 502;
const ll MOD = 1000000007;
const int iNF = 0x3f3f3f3f;

int n, e, q, dis[MAXN][MAXN];

void floyd_washall () {
    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (dis[i][k] != iNF && dis[k][j] != iNF) {
                    dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
                }
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> e >> q;
    memset(dis, iNF, sizeof(dis));
    REP (i, e) {
        int f, t, w;
        cin >> f >> t >> w;
        dis[f][t] = min(dis[f][t], w);
    }

    floyd_washall();

    while (q--) {
        int f, t;
        cin >> f >> t;
        if (dis[f][t] == iNF) {
            cout << "No" << endl;
        } else {
            cout << dis[f][t] << endl;
        }

    }
}
