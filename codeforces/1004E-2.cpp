#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int n, k;
vector<pair<int,int> > edge[MAXN];

int dis[MAXN], deg[MAXN];
bool vis[MAXN];

bool check (int md) { // prune nodes and check remaining graph
    queue<int> que;
    for (int i=1; i<=n; i++) {
        if (edge[i].size() == 1) {
            que.emplace(i);
        }
        deg[i] = edge[i].size();
        dis[i] = 0;
        vis[i] = 0;
    }

    int cnt = n;
    while (que.size()) {
        if (cnt == 1) {
            break;
        }
        int nd = que.front();
        que.pop();

        pair<int,int> p = {-1, -1};
        for (auto v : edge[nd]) {
            if (!vis[v.first]) {
                p = v;
            }
        }

        assert(p.first != -1);

        if (dis[nd] + p.second <= md) { // cut the node
            dis[p.first] = max(dis[p.first], dis[nd] + p.second);
            vis[nd] = true;
            if (--deg[p.first] == 1) {
                que.emplace(p.first);
            }
            cnt--;
        }
    }

    int mxd = 0;
    for (int i=1; i<=n; i++) {
        mxd = max(mxd, deg[i]);
    }

    return mxd <= 2 && cnt <= k;
}
int main () {
    cin >> n >> k;
    for (int i=0; i<n-1; i++) {
        int u, v, w;
#ifdef tmd
        u = i + 2;
        v = rand() % (i+1) + 1;
        w = rand() % 10 + 1;

        cerr << u << " " << v << " " << w << endl;
#else
        cin >> u >> v >> w;
#endif
        edge[u].emplace_back(v, w);
        edge[v].emplace_back(u, w);
    }

    int L = -1, R = 1000000000;
    while (L < R - 1) {
        int M = (L + R) >> 1;
        if (check(M)) {
            R = M;
        } else {
            L = M;
        }
    }

    cout << R << endl;
}
