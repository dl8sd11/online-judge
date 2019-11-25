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

const int MAXN = 402;
const ll MOD = 1000000007;

int n, m, e;
vector<int> edge[MAXN];
int mx[MAXN], my[MAXN];
bool vis[MAXN];

bool dfs (int nd) {
    if (vis[nd]) {
        return false;
    }
    vis[nd] = true;
    for (auto y : edge[nd]) {
        if (my[y] == 0 || dfs(my[y])) {
            mx[nd] = y;
            my[y] = nd;
            return true;
        }
    }

    return false;
}

void greedy_match (int &cnt) {
    REP1 (i, n) {
        for (auto x : edge[i]) {
            if (my[x] == 0) {
                mx[i] = x;
                my[x] = i;
                cnt++;
                break;
            }
        }
    }
}

int max_matching () {
    int cnt = 0;
    greedy_match(cnt);
    REP1 (i, n) {
        if (mx[i] == 0) {
            memset(vis, 0, sizeof(vis));
            cnt += dfs(i);
        }
    }
    return cnt;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> e;
    while (e--) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
    }

    cout << max_matching() << endl;
}
