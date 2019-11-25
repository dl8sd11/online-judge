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


int t, m;
vector<int> vert;
vector<pair<int,int> > edge;
set<int> vis;
map<int, vector<int> > G;
map<int, int> eid;

int dfs (int nd) {
    int lst = nd;
    vis.insert(nd);
    for (int v : G[nd]) {
        if (!vis.count(v)) {
            lst = dfs(v);
        }
    }
    return lst;
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> m;
        vert.clear();
        edge.clear();
        vis.clear();
        G.clear();
        eid.clear();

        REP1 (i, m) {
            int u, v;
            cin >> u >> v;
            edge.emplace_back(u, v);
            eid[u] = i;
            eid[v] = i;

            G[u].emplace_back(v);
            G[v].emplace_back(u);
            vert.emplace_back(u);
            vert.emplace_back(v);
        }

        sort(vert.begin(), vert.end());
        vert.resize(unique(vert.begin(), vert.end())-vert.begin());


        vector<int> endpts;
        for (auto v : vert) {
            if (vis.count(v) == 0) {
                int leaf = dfs(v);
                endpts.emplace_back(leaf);
            }
        }

        cout << SZ(endpts) - 1 << endl;
        for (int i=1; i<SZ(endpts); i++) {
            int nd = endpts[i], ed = eid[nd];
            cout << ed << " " << nd << " " << endpts.front() << endl;
        }


    }

}
