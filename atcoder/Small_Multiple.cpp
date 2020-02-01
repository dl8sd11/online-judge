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

typedef pair<ll,ll> pii;

int k;
ll dis[MAXN];
bool vis[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> k;

    priority_queue<pii, vector<pii>, greater<pii> > pq;

    memset(dis, 0x3f3f3f3f3f3f3f3f,sizeof(dis));
    REP1 (i, 9) {
        if (dis[i%k] > i) {
            dis[i%k] = i;
            pq.emplace(dis[i%k], i%k);
        }
    }

    while (pq.size()) {
        ll cur = pq.top().second;
        pq.pop();
        if (vis[cur]) {
            continue;
        }
        vis[cur] = true;

        REP (i, 10) {
            ll x = (cur*10 + i) % k;
            if (dis[x] > dis[cur] + i) {
                dis[x] = dis[cur] + i;
                pq.emplace(dis[x], x);
            }
        }
    }

    cout << dis[0] << endl;
}
