#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> edge[MAXN];
bool vis[MAXN];
int n,m,ans[MAXN],dis[MAXN];
int cnt[MAXN];
int main () {
    cin >> n >> m;
    m+=n-1;
    while (m--) {
        int f,t;
        cin >> f >> t;
        edge[f].emplace_back(t);
        cnt[t]++;
    }
    queue<int> pq;
    memset(dis,-1,sizeof dis);
    for (int i=1;i<=n;i++) {
        if(cnt[i] == 0) {
            dis[i] = 0;
            pq.emplace(i);
        }
    }

    while (pq.size()) {
        for (auto v : edge[pq.front()]) {
            dis[v] = max(dis[v],dis[pq.front()]+1);
            if (--cnt[v] == 0) {
                pq.emplace(v);
            }
        }
        pq.pop();
    }

    

    for (int i=1;i<=n;i++) {
        for (auto v : edge[i]) {
            if (dis[v] == dis[i] + 1) {
                ans[v] = i;
            }
        }
    }

    for (int i=1;i<=n;i++) {
        cout << ans[i] << endl;
    }

}