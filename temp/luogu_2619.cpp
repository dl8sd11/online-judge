#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, color, wei, swei;
    bool operator < (const Edge &oth) const {
        if (swei == oth.swei) return color < oth.color;
        else return swei < oth.swei;
    }
};

using ve = vector<Edge>;
using pii = pair<int,int>;

struct Djs {
    vector<int> djs;
    Djs (int n) {
        djs.resize(n);
        iota(djs.begin(), djs.end(), 0);
    }
    int fnd (int x) {
        return x == djs[x] ? x : djs[x] = fnd(djs[x]);
    }
    bool mrg (int x, int y) {
        x = fnd(x), y = fnd(y);
        if (x == y) return false;
        djs[x] = y;
        return true;
    }
};

pii mst (int n, ve &edges, int p) {
    for (Edge &e : edges) {
        e.swei = e.color ? e.wei : e.wei - p;
    }
    sort(edges.begin(), edges.end());
    Djs comp(n);

    pii res;
    for (const Edge &e : edges) {
        if (comp.mrg(e.u, e.v)) {
            res.first += e.color == 0;
            res.second += e.swei;
        }
    }
    return res;
}

int main () {
    int n, m, need;
    cin >> n >> m >> need;
    ve edges;

    for (int i=0; i<m; i++) {
        int u, v, w, col;
        cin >> u >> v >> w >> col;
        edges.push_back({u, v, col, w, 0});
    }

    int L = -102, R = 102;
    while (L < R - 1) {
        int M = (L + R) >> 1;
        if (mst(n, edges, M).first >= need) R = M;
        else L = M;
    }

    pii res = mst(n, edges, R);
    cout << res.second + R * need << endl;
}
