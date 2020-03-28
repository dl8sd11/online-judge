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
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, b[MAXN], c[MAXN];
vector<int> edge[MAXN];
vector<int> node;

int djs[MAXN], sz[MAXN], comp;

void init () {
    REP (i, SZ(node)) {
        djs[i] = i;
        sz[i] = 1;
    }
    comp = SZ(node);
}

int fnd (int nd) {
    return djs[nd] == nd ? nd : djs[nd] = fnd(djs[nd]);
}

void mrg (int u, int v) {
    u = fnd(u), v = fnd(v);
    if (u == v) {
        return;
    }
    if (sz[u] > sz[v]) {
        swap(u, v);
    }
    djs[u] = v;
    sz[v] += sz[u];
    comp--;
}

vector<int> xedge;
bool vis[MAXN];
int cur[MAXN];
vector<int> ans;

void dfs (int nd) {
    for (int &i=cur[nd]; i<SZ(edge[nd]); i++) {
        int eid = edge[nd][i];
        int v = xedge[eid] ^ nd;
        if (!vis[eid]) {
            vis[eid] = true;
            dfs(v);
        }
    }
    ans.eb(nd);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    n--;

    bool flag = false;
    REP (i, n) {
        #ifdef tmd
        b[i] = 1;
        #else
        cin >> b[i];
        #endif // tmd
        node.eb(b[i]);
    }
    REP (i, n) {
        #ifdef tmd
        c[i] = 1;
        #else
        cin >> c[i];
        #endif // tmd
        node.eb(c[i]);
    }

    sort(ALL(node));
    node.resize(unique(ALL(node))-node.begin());
    init();

    REP (i, n) {
        flag |= b[i] > c[i];
        b[i] = lower_bound(ALL(node),b[i])-node.begin();
        c[i] = lower_bound(ALL(node),c[i])-node.begin();
    }

    REP (i, n) {
        xedge.eb(b[i] ^ c[i]);
        edge[b[i]].eb(i);
        edge[c[i]].eb(i);
        mrg(b[i], c[i]);
    }

    vector<int> odd;
    REP (i, SZ(node)) {
        if (SZ(edge[i]) & 1) {
            odd.eb(i);
        }
    }


    debug(comp, odd);

    if (flag || comp != 1 || (SZ(odd) != 0 && SZ(odd) != 2)) {
        cout << -1 << endl;
    } else {
        dfs(odd.empty() ? 0 : odd.back());
        REP (i, n+1) {
            cout << node[ans[i]] << " \n"[i==n];
        }
    }


}
