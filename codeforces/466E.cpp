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

int djs[MAXN], sz[MAXN];

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void uni (int x, int y) {
    x = fnd(x), y = fnd(y);
    djs[x] = y;
}

int n, m;
struct Modify {
    int u, v, t;
};
vector<Modify> modify;

int qcnt;
bool ans[MAXN];
struct Query {
    int u, t;
    vector<pair<int,int> > v;
};
vector<Query> query;

int deg[MAXN], in[MAXN], out[MAXN], tme;
vector<int> edge[MAXN];

void dfs (int nd) {
    in[nd] = tme++;
    for (auto v : edge[nd]) {
        dfs(v);
    }
    out[nd] = tme++;
}

bool isAnc (int p, int d) {
    return in[p] <= in[d] && out[p] >= out[d];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (t, m) {
        debug(t);
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int u, v;
            cin >> u >> v;
            modify.push_back({u, v, t});
            edge[v].emplace_back(u);
            deg[u]++;
        } else if (cmd == 2) {
            int x;
            cin >> x;
            query.push_back({x, t, {}});
        } else {
            int x, i;
            cin >> x >> i;
            i--;
            query[i].v.emplace_back(x, qcnt++);
        }
    }
    REP1 (i, n) {
        if (deg[i] == 0) {
            dfs(i);
        }
    }

    REP1 (i, n) {
        djs[i] = i;
    }

    int ptr = 0;
    for (auto Q : query) {
        while (ptr < SZ(modify) && modify[ptr].t < Q.t) {
            uni(modify[ptr].u, modify[ptr].v);
            ptr++;
        }
        for (auto tst : Q.v) {
            ans[tst.second] = fnd(tst.first) == fnd(Q.u) && isAnc(tst.first, Q.u);
        }
    }


    REP (i, qcnt) {
        cout << (ans[i] ? "YES" : "NO") << endl;
    }
    return 0;
}
