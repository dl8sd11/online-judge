#include <bits/stdc++.h>
using namespace std;
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

const int MAXN = 100005;

int n, k, hei[MAXN];
bool vis[MAXN];
vector<int> edg[MAXN];

void dfs_pre (int nd) {
    hei[nd] = 1;
    for (auto v : edg[nd]) {
        dfs_pre(v);
        hei[nd] = max(hei[nd], hei[v] + 1);
    }
}

int ans;
void dfs_solve (int nd) {
    vis[nd] = true;
    ans++;
    int mx = -1;
    for (auto v : edg[nd]) {
        if (!vis[v]) {
            if (mx == -1) {
                mx = v;
            } else if (hei[v] > hei[mx]) {
                mx = v;
            }
        }
    }

    if (mx != -1) {
        dfs_solve(mx);
    }
}
/****GOOD_LUCK****/
int main () {
    IOS();

    cin >> n >> k;
    for (int i=2; i<=n; i++) {
        int p;
        cin >> p;
        edg[p].emplace_back(i);
    }

    dfs_pre(1);
    vector<int> id;
    REP1 (i, n) {
        id.emplace_back(i);
    }
    sort(id.begin(), id.end(), [](int a, int b) {
        return hei[a] > hei[b];
    });


    for (auto v : id) {
        if (!vis[v] && k-- > 0) {
            dfs_solve(v);
        }
    }

    cout << ans << endl;
    return 0;
}
