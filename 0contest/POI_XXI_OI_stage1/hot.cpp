#include <bits/stdc++.h>
using namespace std;
typedef int ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define X first
#define Y second
#define SZ(i) ll(i.size())
#define MEM(i,n) memset(i,(n),sizeof(i))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define endl '\n'
#endif
const ll MAXN = 600;
const ll INF = 0x3f3f3f3f;
ll n;
ll dis[MAXN][MAXN];

int main () {
    cin >> n;
    assert(n < MAXN);
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        dis[u][v] = 1;
        dis[u][v] = 1;
    }

    REP1 (k,n) {
        REP1 (i,n) {
            REP1 (j,n) {
                if (dis[i][k] < INF && dis[k][j] < INF) {
                    dis[i][j] = min(dis[i][j],dis[i][k],dis[k][j]);
                }
            }
        }
    }
    ll ans = 0;
    REP1 (i,n) {
        REP1 (j,i-1) {
            REP1 (k,j-1) {
                if (dis[i][j] == dis[k][j] && dis[k][j] ==dis[i][k]) {
                    ans++;
                }
            }
        }
    }

    cout << ans << endl;
}