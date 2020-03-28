#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
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
template<typename T> ostream &operator << (ostream &os,array<T,2> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 10004;
const ll MOD = 1000000007;

int n, m, k;
vector<int> edge[MAXN], tree[MAXN];
map<int,array<int,2> > real_tree[MAXN];
vector<vector<int> > bcc;
int ccid[MAXN];

vector<int> req[MAXN];
bitset<MAXN> used[MAXN];


vector<int> stk;
int low[MAXN], dfn[MAXN], tme;
void dfs_bcc (int nd, int par) {
    stk.eb(nd);
    low[nd] = dfn[nd] = ++tme;

    for (auto v : edge[nd]) {
        if (v != par) {
            if (dfn[v] == 0) {
                dfs_bcc(v, nd);
                low[nd] = min(low[nd], low[v]);
            } else {
                low[nd] = min(low[nd], dfn[v]);
            }
        }
    }

    assert(low[nd] <= dfn[nd]);
    if (low[nd] == dfn[nd]) {
        vector<int> cur;
        do {
            cur.eb(stk.back());
            ccid[stk.back()] = SZ(bcc);
            stk.pop_back();
        } while (cur.back() != nd);
        bcc.eb(cur);
    }
}

vector<array<int,2> > ans;
bool inCC[MAXN], vis[MAXN];
int sz = 0;

#define pb push_back
void dfs_scc (int nd, int par) {
    dfn[nd] = ++tme;

    for (auto v : edge[nd]) {
        if (inCC[v] && v != par) {
            if (dfn[v] == 0) {
                ans.pb({nd, v});
                dfs_scc(v, nd);
            } else if (dfn[v] < dfn[nd]) {
                ans.pb({nd, v});
            }
        } else if (!inCC[v]) {
            tree[ccid[nd]].eb(ccid[v]);
            real_tree[ccid[nd]][ccid[v]] = {nd, v};
            debug(ccid[nd], ccid[v]);
            sz++;
        }
    }
}

bool tar[MAXN];

bool dfs_tree (int nd, int par) {
    bool ret = tar[nd];
    for (auto v : tree[nd]) {
        if (v != par) {
            bool res = dfs_tree(v, nd);
            ret |= res;
            if (res) {
                if (used[v][nd]) {
                    cout << "No" << endl;
                    exit(0);
                }
                if (!used[nd][v]) {
                    used[nd][v] = true;
                    ans.pb(real_tree[nd][v]);
                }
            }
        }
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    // the graph is connected
    dfs_bcc(1, 1);
    debug(bcc);

    for (auto cc : bcc) {
        for (auto nd : cc) {
            inCC[nd] = true;
            dfn[nd] = 0;
        }

        debug(cc);
        tme = 0;
        dfs_scc(cc.back(), -1);

        for (auto nd : cc) {
            inCC[nd] = false;
        }
    }
    assert(sz == (SZ(bcc) - 1) * 2);

    debug(ans);

    cin >> k;
    REP (i, k) {
        int f, t;
        cin >> f >> t;
        if (ccid[f] != ccid[t]) {
            req[ccid[f]].eb(ccid[t]);
        }
    }

    REP (i, SZ(bcc)) {

        for (auto id : req[i]) {
            tar[id] = true;
        }

        dfs_tree(i, -1);

        for (auto id : req[i]) {
            tar[id] = false;
        }
    }

    REP (nd, SZ(bcc)) {
        for (auto v : tree[nd]) {
            if (!used[v][nd] && !used[nd][v]) {
                used[v][nd] = true;
                ans.pb(real_tree[nd][v]);
            }
        }
    }

    assert(SZ(ans) == m);
    cout << "Yes" << endl;
    for (auto e : ans) {
        cout << e[0] << " " << e[1] << endl;
    }


}
/*
9 11
1 2
2 3
2 6
3 6
3 4
4 5
3 5
6 7
7 8
8 9
7 9
*/
