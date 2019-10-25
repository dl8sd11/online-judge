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

const int MAXN = 1003;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

int n, m, lst[MAXN];
bool vis[MAXN];
vector<int> edge[MAXN];


vector<int> ans;

void solve (int src) {
    memset(vis, 0, sizeof(bool) * (n+1));
    vis[src] = true;
    vector<int> que = {src};
    int ft = 0;


    while (ft < SZ(que)) {
        int cur = que[ft++];
        for (auto v : edge[cur]) {
            if (!vis[v]) {
                lst[v] = cur;
                que.emplace_back(v);
                vis[v] = true;
            } else if (v == src) {
                debug("test");
                vector<int> cycle = {src};
                while (cur != src) {
                    cycle.emplace_back(cur);
                    cur = lst[cur];
                }
                if (ans.empty() || SZ(cycle) < SZ(ans)) {
                    ans = cycle;
                }
                return;
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int f, t;
        cin >> f >> t;
        edge[f].emplace_back(t);
    }

    REP1 (i, n) {
        debug(i);
        solve(i);
    }

    if (ans.empty()) {
        cout << -1 << endl;
    } else {
        cout << SZ(ans) << endl;
        for (auto v : ans) {
            cout << v << endl;
        }
    }
    return 0;
}
