#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define SZ(i) int(i.size())

const int MAXN = 100005;
const int MAXLG = __lg(MAXN) + 2;

int n, k, dp[MAXN], di[MAXN], dep[MAXN], anc[MAXLG][MAXN];
array<int,4> bst[MAXN];

vector<int> edge[MAXN];

void build_lca () {
    for (int i=1; i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int dis (int u, int v) {
    int ou = u, ov = v;
    if (dep[u] > dep[v]) {
        swap(u,v);
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    if (u == v) {
       return dep[ou] + dep[ov] - 2*dep[u];
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (anc[i][v] != anc[i][u]) {
            v = anc[i][v];
            u = anc[i][u];
        }
    }
    return dep[ou] + dep[ov] - 2*dep[anc[0][u]];
}

struct Dia {
    int u, v, d;
    Dia () {
    }

    Dia (int nd) {
        u = v = nd;
        d = 0;
    }
} pre[MAXN], suf[MAXN];
int nid[MAXN], in[MAXN], out[MAXN], dfc;

Dia mrg (const Dia &d1, const Dia &d2) {
    int u, v, d = 0;
    vector<int> can = {d1.u, d1.v, d2.u, d2.v};
    for (auto n1 : can) {
        for (auto n2 : can) {
            int cd = dis(n1, n2);
            if (cd > d) {
                u = n1;
                v = n2;
                d = cd;
            }
        }
    }
    Dia ret;
    ret.u = u;
    ret.v = v;
    ret.d = d;
    return ret;
}

Dia mrg (const Dia &d1, const int nd) {
    return mrg(d1, Dia(nd));
}

void dfs1 (int nd, int par) {
    nid[dfc] = nd;
    in[nd] = dfc++;

    dep[nd] = dep[par] + 1;
    anc[0][nd] = par;

    for (auto v : edge[nd]) {
        if (v != par) {
           dfs1(v, nd);
           di[nd] = max(di[nd], di[v]);

           for (int i=0; i<4; i++) {
               if (dp[v] + 1 > bst[nd][i]) {
                   for (int j=2; j>=i; j--) {
                       bst[nd][j+1] = bst[nd][j];
                   }
                   bst[nd][i] = dp[v] + 1;
                   break;
               }
           }
        }
    } 
    di[nd] = max(di[nd], bst[nd][0] + bst[nd][1]);
    dp[nd] = bst[nd][0];

    out[nd] = dfc;
}

int main () {
    cin >> n >> k;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs1(1, 0);
    build_lca();

    if (k == 1) {

        cout << (n-1) * 2 - di[1] + 1 << endl;
    } else {
        pre[0] = Dia(nid[0]);
        for (int i=1; i<n; i++) {
            pre[i] = mrg(pre[i-1], nid[i]);
        }

        suf[n-1] = Dia(nid[n-1]);
        for (int i=n-2; i>=0; i--) {
            suf[i] = mrg(suf[i+1], nid[i]);
        }

        int bs = 0;
        for (int i=1; i<=n; i++) {

            
            vector<int> cur;
            for (int j=0; j<4; j++) {
                cur.eb(bst[i][j]);
            }

            if (i != 1) {
                Dia tp = mrg(pre[in[i]-1], suf[out[i]]);
                bs = max(bs, tp.d + di[i]);
                cur.eb(max(dis(tp.u,i), dis(tp.v,i)));
            }

            sort(cur.begin(), cur.end());
            if (SZ(edge[i]) >= 4) {
                int sum = 0;
                for (int j=0; j<4; j++) {
                    sum += cur[SZ(cur)-j-1];
                }
                bs = max(bs, sum);
            }
        }

        cout << (n-1) * 2 - bs + 2 << endl;
    }
}
