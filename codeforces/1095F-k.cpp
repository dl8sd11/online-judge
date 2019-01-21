#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct E {
    int u,v;
    ll w;
    bool operator < (const E &e) {
        return w < e.w;
    }
};
vector<E> edge;
int n,m;
ll a[200003],ans;;

int djs[200003],sz[200003];
void init() {
    for (int i=0;i<n;i++) {
        djs[i] = i;
        sz[i] = 1;
    }
}

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void uni (int x,int y) {
    if (sz[x=fnd(x)] > sz[y=fnd(y)]) {
        swap(x,y);
    }
    djs[x] = y;
    sz[y] += sz[x];
}
int main () {
    cin >> n >> m;
    init();

    int minid = 0;
    for (int i=0;i<n;i++) {
        cin >> a[i];
        if (a[i] < a[minid]) {
            minid = i;
        }
    }

    for (int i=0;i<n;i++) {
        if (i != minid) {
            edge.push_back({i,minid,a[i]+a[minid]});
        }
    }

    for (int i=0;i<m;i++) {
        int u,v;
        ll w;
        cin >> u >> v >> w;
        u--,v--;
        edge.push_back({u,v,w});
    }

    sort(edge.begin(),edge.end());

    for (int i=0;i<int(edge.size());i++) {
        if (fnd(edge[i].u) != fnd(edge[i].v)) {
            cout << "Connected: " << edge[i].u << " " << edge[i].v << endl;
            uni(edge[i].u,edge[i].v);
            ans += edge[i].w;
        }
    }

    cout << ans << endl;
}