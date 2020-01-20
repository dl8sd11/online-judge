#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n;
vector<int> edge[MAXN];
map<pair<int,int>,int> eid;
vector<int> cycle;
bool onCycle[MAXN], vis[MAXN];
int deg[MAXN];

int ans[MAXN], dia[MAXN];

void build_cycle (int nd) {
    vis[nd] = true;
    cycle.emplace_back(nd);
    for (auto v : edge[nd]) {
        if (onCycle[v] && !vis[v]) {
            build_cycle(v);
        }
    }
}

int dp[MAXN][2];
int gdia;
void solve_dia (int nd, int par) {
    dp[nd][0] = dp[nd][1] = 0;
    for (auto v : edge[nd]) {
        if (v != par && !onCycle[v]) {
            solve_dia(v, nd);
            if (dp[v][0]+1 >= dp[nd][0]) {
                dp[nd][1] = dp[nd][0];
                dp[nd][0] = dp[v][0] + 1;
            } else if (dp[v][0]+1 > dp[nd][1]) {
                dp[nd][1] = dp[v][0] + 1;
            }
        }
    }
    dia[nd] = dp[nd][0] + dp[nd][1];
    gdia = max(gdia, dia[nd]);
}


/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int u, v;
        cin >> u >> v;
        if (u > v) {
            swap(u, v);
        }
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
        deg[u]++;
        deg[v]++;

        eid[{u,v}] = i;
    }
    debug("inputed");

    fill(onCycle,onCycle+n+1, true);
    { // build cycle
        queue<int> bfs;
        REP1 (i, n) {
            if (deg[i] == 1) {
                bfs.emplace(i);
            }
        }

        while (bfs.size()) {
            int cur = bfs.front();
            bfs.pop();
            debug(cur);
            onCycle[cur] = false;
            for (auto v : edge[cur]) {
                if (--deg[v] == 1) {
                    bfs.emplace(v);
                }
            }
        }

        int root = 0;
        REP1 (i, n) {
            if (onCycle[i]) {
                root = i;
                break;
            }
        }

        build_cycle(root);
        debug(cycle);
    }

    for (auto v : cycle) {
        solve_dia(v, v);
    }
    pary(dia+1, dia+1+n);
    debug(gdia);


    REP (i, n) {
        cout << ans[i] << endl;
    }
}
