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
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;

typedef pair<int,int> pii;

int n, ans[MAXN], anc[MAXN];
string name[MAXN];
vector<int> edge[MAXN], root;
vector<pii> qry[MAXN];
bool big[MAXN];

int sz[MAXN], son[MAXN], dep[MAXN];

void makeInfo (int nd) {
    sz[nd] = 1;
    dep[nd] = dep[anc[nd]] + 1;
    for (auto v : edge[nd]) {
        makeInfo(v);
        sz[nd] += sz[v];
        if (sz[v] > sz[son[nd]]) {
            son[nd] = v;
        }
    }
}

map<string, int> cnt[MAXN];
void addTree (int nd, bool b) {
    if (b) {
        cnt[dep[nd]][name[nd]]++;
    } else {
        if (cnt[dep[nd]][name[nd]]-- == 1) {
            cnt[dep[nd]].erase(name[nd]);
        }
    }
    for (auto v : edge[nd]) {
        if (!big[v]) {
            addTree(v, b);
        }
    }
}

void solve (int nd, bool keep) {
    for (auto v : edge[nd]) {
        if (v != son[nd]) {
            solve(v, 0);
        }
    }
    if (son[nd]) {
        solve(son[nd], 1);
        big[son[nd]] = true;
    }
    addTree(nd, true);

    for (auto p : qry[nd]) {
        if (dep[nd]+p.second < MAXN) {
            ans[p.first] = cnt[dep[nd]+p.second].size();
        }
    }

    big[son[nd]] = false;
    if (!keep) {
        addTree(nd, false);
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> name[i];
        cin >> anc[i];
        if (anc[i] == 0) {
            root.emplace_back(i);
        }
        edge[anc[i]].emplace_back(i);
    }

    int m;
    cin >> m;
    REP (i, m) {
        int v, k;
        cin >> v >> k;
        qry[v].emplace_back(i, k);
    }

    for (auto r : root) {
        makeInfo(r);
        solve(r, 0);
    }

    REP (i, m) {
        cout << ans[i] << endl;
    }
}
