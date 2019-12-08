#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

vector<vector<pair<int,int> > > orgEdge;

void init (int n) {
    orgEdge.resize(n);
}

void add_edge (int u, int v, int k) {
    orgEdge[u].emplace_back(v, k);
    orgEdge[v].emplace_back(u, k);
}

struct HLD {
    // all param should be component id not node id
    int lca;

    void addEdgeNodeInclusive (int u, int v, int k) {

    }

    int qryBridge (int u, int v) {

    }

    int qryNodeExcludeRootUV (int u, int v) {

    }

    pair<int,int> getLCASon (int u, int v) { // returns node id

    }

    int getEndpointParent (int u) { // returns node id

    }
};

struct MST {
    int qryPathMax (pair<int,int> node) {

    }
};

struct BCC {
    int componentId[MAXN];
    vector<vector<int> > component;
    vector<pair<int,int> > bridge;

    void build_bcc (int nd, int par) {

    }
};

struct Solver {
    HLD pathNodeEdge;
    BCC componentGraph;
    vector<MST> componentMST;

    void buildAgents () {

    }

    void addPath (int u, int v, int k) {
        pathNodeEdge.addEdgeNodeInclusive(u, v, k);
    }

    int qryPathMax (int u, int v) {
        int uCompId = componentGraph.componentId[u];
        int vCompId = componentGraph.componentId[v];

        int ret = pathNodeEdge.qryBridge(uCompId, vCompId);
        ret = max(ret, pathNodeEdge.qryNodeExcludeRootUV(uCompId, vCompId));

        pair<int,int> lcaSon = pathNodeEdge.getLCASon(vCompId, uCompId);
        ret = max(ret, componentMST.qryPathMax(lcaSon));

        pair<int,int> uEndpoint = {u, pathNodeEdge.getEndpointParent(uCompId)};
        pair<int,int> vEndpoint = {v, pathNodeEdge.getEndpointParent(vCompId)};
        ret = max(ret, componentMST.qryPathMax(uEndPoint));
        ret = max(ret, componentMST.qryPathMax(vEndPoint));

        return ret;
    }

} solver;

int main () {
    int _T, n, m, q;
    cin >> _T;

    cin >> n >> m >> q;
    init(n);

    REP (i, m) {
        int u, v, k;
        cin >> u >> v >> k;
        add_edge(u, v, k);
    }

    buildAgents();

    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 0) {
            int a, b, k;
            cin >> a >> b >> k;
            solver.addPath(a, b, k);
        } else {
            int a, b;
            cin >> a >> b;
            cout << solver.qryPath(a, b) << endl;
        }
    }
}
