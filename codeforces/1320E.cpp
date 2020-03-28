#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;
const int MAXLG = __lg(MAXN) + 2;

int n, q;
vector<int> edge[MAXN];

int dep[MAXN], in[MAXN], out[MAXN], anc[MAXLG][MAXN], tme;

void dfs (int nd, int par) {
    dep[nd] = dep[par] + 1;
    in[nd] = tme++;
    anc[0][nd] = par;

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }
    out[nd] = tme++;
}

void build_lca () {
    REP1 (i, MAXLG - 1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int lca (int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u,v);
    }

    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i=MAXLG-1; i>=0; i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    return anc[0][u];
}

bool isPar (int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

int ans[MAXN];
struct VirtualTree {
    vector<int> ctp;
    vector<int> edge[MAXN];
    vector<int> node;
    vector<int> stk;

    void clear () {
        for (auto v : node) {
            edge[v].clear();
            ans[v] = -1;
        }
        ctp.clear();
        node.clear();
        stk.clear();
    }

    void print () {
        for (auto v : node) {
            debug(v);
            debug(edge[v]);
        }
    }

    void addEdge (int u, int v) {
        edge[u].eb(v);
        edge[v].eb(u);
    }

    void insert (int nd) {
        if (nd != 1) { // 1 is always in virtual tree
            ctp.eb(nd);
        }
    }

    void build () {
        sort(ALL(ctp), [&](int u, int v) {
            return in[u] < in[v];
        });
        ctp.resize(unique(ALL(ctp))-ctp.begin());

        node.eb(1);
        stk.eb(1);

//        debug(ctp);
        for (auto v : ctp) {
//            debug(v);
            int ca = lca(stk.back(), v);
            if (ca != stk.back()) {
                while (stk.size() >= 2 && dep[stk[SZ(stk)-2]] >= dep[ca]) {
                    addEdge(stk.back(), stk[SZ(stk)-2]);
                    stk.pop_back();
                }

                if (stk.back() != ca) {
                    addEdge(ca, stk.back());
                    stk.pop_back();
                    stk.eb(ca);
                    node.eb(ca);
                }
            }

            stk.eb(v);
            node.eb(v);
        }

        while (stk.size() >= 2) {
            addEdge(stk.back(), stk[SZ(stk)-2]);
            stk.pop_back();
        }
    }
};


int dis (int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u,v)];
}

VirtualTree vt;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1, 1);
    build_lca();

    cin >> q;

    memset(ans, -1, sizeof(ans));
    while (q--) {

        int k, m;
        cin >> k >> m;

        vector<pair<int,int> > vir;
        vector<int> imp;


        REP (i, k) {
            int v, s;
            cin >> v >> s;
            vir.eb(v, s);
            vt.insert(v);
        }

        REP (i, m) {
            int v;
            cin >> v;
            imp.eb(v);
            vt.insert(v);
        }

        vt.build();
//        vt.print();

        priority_queue<pli, vector<pli>, greater<pli> > pq;

        REP (i, k) {
            pq.emplace(i, vir[i].X);
        }


        while (pq.size()) {
            int cur = pq.top().Y;
            if (ans[cur] != -1) {
                pq.pop();
                continue;
            }
//            debug(cur, pq.top().X);

            ans[cur] = pq.top().X % k;
            pq.pop();

            int tp = ans[cur];
            for (auto v : vt.edge[cur]) {
                int d = dis(vir[tp].X, v);
//                debug(d, cur, v);
                d = (d + vir[tp].Y - 1)  / vir[tp].Y;

                if (ans[v] == -1) {
                    pq.emplace(d*k+tp, v);
                }
            }
        }

        for (auto v : imp) {
            cout << ans[v] + 1 << " ";
        }
        cout << endl;

        vt.clear();
    }
}

/*
7
1 2
1 3
2 4
2 5
3 6
3 7
3
2 2
4 1
7 1
1 3
2 2
4 3
7 1
1 3
3 3
1 1
4 100
7 100
1 2 3
*/
