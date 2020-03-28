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
template<typename T> ostream &operator << (ostream &os,array<T,3> &v){return _printRng(os,v.begin(), v.end());}
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

int csz;

typedef array<int,3> ai3; // ans, min, max

ai3 seg[MAXN*4];

ai3 mrg (const ai3 &s1, const ai3 &s2) {
    ai3 res;
    res[0] = max({s1[0], s2[0], s1[1]+s2[2]});
    res[1] = max(s1[1], s2[1]);
    res[2] = max(s1[2], s2[2]);
    return res;
}

void build_seg () {
    for (int i=csz*2-1; i>0; i--) {
        seg[i] = mrg(seg[i<<1], seg[i<<1|1]);
    }
}

#define eb emplace_back
#define ALL(i) i.begin(),i.end()

int qry (int l, int r) {
    int res = 0;
    vector<int> L, R;
    for (l+=csz*2, r+=csz*2;l<r;l>>=1, r>>=1) {
        if (l&1) {
            L.eb(l++);
        }
        if (r&1) {
            R.eb(--r);
        }
    }

    reverse(ALL(R));
    for (auto v : R) {
        L.eb(v);
    }
    debug(L);

    ai3 cur = seg[L[0]];

    for (int i=1; i<SZ(L); i++) {
        cur = mrg(cur, seg[L[i]]);
    }

    debug(cur);
    return cur[0];
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

        csz = SZ(cycle);
    }

    for (auto v : cycle) {
        solve_dia(v, v);
    }
    pary(dia+1, dia+1+n);
    debug(gdia);

    memset(ans, -1, sizeof(ans));
    { // include cycle

        for (int i=0;i<csz*2; i++) {
            seg[i+csz*2][0] = -0x3f3f3f3f;
            seg[i+csz*2][1] = -i+dp[cycle[i%csz]][0];
            seg[i+csz*2][2] = i+dp[cycle[i%csz]][0];

            debug(seg[i+csz*2]);
        }
        build_seg();

        for (int i=0;i<csz;i++) {
            pair<int,int> cur = {cycle[i], cycle[(i+1)%csz]};
            if (cur.first > cur.second) {
                swap(cur.first, cur.second);
            }


            int c = qry(i+1, i+csz+1);

            int id = eid[cur];
            debug(c, cur.first ,cur.second, id);
            ans[id] = max(c, gdia);
        }
    }


    REP (i, n) {
        cout << ans[i] << endl;
    }
}
