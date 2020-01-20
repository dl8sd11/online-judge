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
const int MAXLG = __lg(MAXN) + 2;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, in[MAXN], out[MAXN], tme, anc[MAXLG][MAXN], dep[MAXN];
vector<int> edge[MAXN];

void dfs (int nd, int par) {
    in[nd] = tme++;
    dep[nd] = dep[par] + 1;
    anc[0][nd] = par;

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }
    out[nd] = tme;
}

void build_anc () {
    for (int i=1;i<MAXLG;i++) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int seg[MAXN*2];

void add (int l, int r, int val) {
    for (l+=n,r+=n;l<r;l>>=1, r>>=1) {
        if (l&1) {
            seg[l++] += val;
        }
        if (r&1) {
            seg[--r] += val;
        }
    }
}

int qry (int x) {
    int ret = 0;
    for (x+=n;x>=1;x>>=1) {
        ret += seg[x];
    }
    return ret;
}

bool is_anc (int x, int y) {
    return in[x]<=in[y] && out[y]<=out[x];
}

int get_child (int nd, int rt) {
    for (int i=MAXLG-1;i>=0;i--) {
        if (dep[anc[i][nd]] > dep[rt]) {
            nd = anc[i][nd];
        }
    }
    return nd;
}

void leave (int f, int t) {
    if (is_anc(f, t)) {
        add(0, n, 1);
        int nd = get_child(t, f);
        debug(nd);

        debug(in[nd], out[nd]);
        add(in[nd],out[nd], -1);
    } else {
        add(in[f],out[f],1);
    }
}

vector<int> dedge[MAXN];
int deg[MAXN];
bool isDag () {
    queue<int> bfs;
    REP1 (i, n) {
        if (deg[i] == 0) {
            bfs.emplace(i);
        }
    }

    int cnt = 0;
    while (bfs.size()) {
        cnt++;
        int nd = bfs.front();
        bfs.pop();
        for (auto v : dedge[nd]) {
            if (--deg[v] == 0) {
                bfs.emplace(v);
            }
        }
    }

    return cnt == n;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    #ifndef tmd

    freopen("gathering.in","r",stdin);
    freopen("gathering.out","w",stdout);

    #endif // tmd

    cin >> n >> m;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    dfs(1,0);
    build_anc();

    pary(in+1,in+n+1);

    REP (i, m) {
        int f, t;
        cin >> f >> t;
        dedge[f].emplace_back(t);
        deg[t]++;
        leave(f, t);
    }

    if (!isDag()) {
        REP1 (i, n) {
            cout << 0 << endl;
        }
    } else {
        REP1 (i, n) {
            debug(i, qry(in[i]));
            cout << (qry(in[i]) == 0) << endl;
        }
    }

}
/*
8 1
1 2
2 3
2 4
3 8
1 5
5 6
5 7
2 8

*/
