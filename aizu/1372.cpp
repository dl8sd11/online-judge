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

const int MAXP = 302;
const int MAXN = 1003;
const ll MOD = 1000000007;


string ps, qs;
int n;

map<string, int> id;
int getID (string &name) {
    if (id.count(name)) {
        return id[name];
    } else {
        int sz = SZ(id);
        id[name] = sz;
        return sz;
    }
}

bool anc[MAXN][MAXP][MAXP];
bool edg[MAXN][MAXP][MAXP];
bool dag[MAXP][MAXP];
vector<int> edge[MAXP];
bool vis[MAXP];

typedef pair<int, int> pii;


void dfs (int nd, int hd, int cl) {
    vis[nd] = true;
    if (nd != hd) {
        anc[cl][hd][nd] = true;
    }
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            dfs(v, hd, cl);
        }
    }
}

bitset<MAXP> g[MAXP];
void add (int x, int y) {
    g[x][y] = true;
    g[x] |= g[y];
    REP (i, MAXP) {
        if (g[i][x]) {
            g[i] |= g[x];
        }
    }
}

void build (int cl) {
    int m;
    cin >> m;

    vector<int> vert;
    REP (i, m) {
        string f, t;
        cin >> f >> t;
        int nf = getID(f), nt = getID(t);
        edge[nf].emplace_back(nt);
        vert.emplace_back(nf);
        edg[cl][nf][nt] = true;
    }

    for (auto v : vert) {
        memset(vis, 0, sizeof(vis));
        dfs(v, v, cl);
    }
    for (auto v : vert) {
        edge[v].clear();
    }
}

bool tru[MAXN], fal[MAXN];
bool visp[MAXP][MAXP], visn[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> ps >> qs;
    cin >> n;
    REP (i, n) {
        build(i);
    }

#ifdef tmdd
    for (auto p : id) {
        debug(p.first, p.second);
    }
    REP (i, n) {
        cout << "-----------------" << endl;
        REP (x, SZ(id)) {
            REP (y, SZ(id)) {
                cout << anc[i][x][y] << " \n"[y==SZ(id)-1];
            }
        }
    }
#endif

    queue<pii> bfs;
    bfs.emplace(getID(ps), getID(qs));

    visp[getID(ps)][getID(qs)] = true;

    while (!bfs.empty()) {
        pii cur = bfs.front();
        bfs.pop();

        REP (i, n) {
            if (edg[i][cur.first][cur.second] && !visn[i]) {
                tru[i] = true;
                visn[i] = true;
                REP (x, SZ(id)) {
                    REP (y, SZ(id)) {
                        if (edg[i][x][y]) {
                            add(x, y);
                        }
                    }
                }

                REP (x, SZ(id)) {
                    REP (y, SZ(id)) {
                        if (g[x][y] && !visp[x][y]) {
                            visp[x][y] = true;
                            bfs.emplace(x, y);
                        }
                    }
                }
            }
        }
    }

    bool err_flag = false;
    REP (x, SZ(id)) {
        REP (y, SZ(id)) {
            if (g[x][y] && g[y][x]) {
                err_flag = true;
            }
        }
    }

    cout << (err_flag ? "No" : "Yes") << endl;

    return 0;
}
