#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[200003];
vector<pair<int,ll> > edge[200003];
ll ans;
bool vis[200003];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;
int main () {
    int n,m;

    cin >> n >> m;
    int minid = 0;
    for (int i=0;i<n;i++) {
        cin >> a[i];
        if (a[i] < a[minid]) {
            minid = i;
        }
    }

    for (int i=0;i<n;i++) {
        if (i != minid) {
            edge[minid].emplace_back(i,a[i]+a[minid]);
            edge[i].emplace_back(minid,a[i]+a[minid]);
        }
    }

    for (int i=0;i<m;i++) {
        int u,v;
        ll w;
        cin >> u >> v >> w;
        u--,v--;
        edge[u].emplace_back(v,w);
        edge[v].emplace_back(u,w);
    }

    pq.emplace(0,0);
    for (int i=0;i<n;i++) {
        while (pq.size() && vis[pq.top().second]) pq.pop();
        pair<ll,int> cur = pq.top();pq.pop();
        vis[cur.second] = true;
        ans += cur.first;
        #ifdef tmd
            cout << "got: " << cur.second + 1 << " " << cur.first << endl;
        #endif
        for (auto e:edge[cur.second]) {
            pq.emplace(e.second,e.first);
        }
    }

    cout << ans << endl;
}