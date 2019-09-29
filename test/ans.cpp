#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif
    
const int MAXN = 1000006;
const ll MOD = 1000000007;
    
int n, a[MAXN], p[MAXN];
double sum[MAXN], sz[MAXN];
vector<int> edge[MAXN];
    
void dfs (int nd) {
    sum[nd] = a[nd];
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        dfs(v);
        sum[nd] += sum[v];
        sz[nd] += sz[v];
    }
    sum[nd] /= sz[nd];
}

#ifdef tmd
vector<int> ord;
bool vis[MAXN];
void pre_dfs (int nd) {
    vis[nd] = true;
    ord.emplace_back(a[nd]);
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            pre_dfs(v);
        }
    }
}

namespace BIT {
    ll bit[MAXN];
    void add (int pos, ll val) {
        pos++;
        for (;pos<MAXN;pos+=-pos&pos) {
            bit[pos] += val;
        }
    }

    ll qry (int pos) {
        ll ret = 0;
        pos++;
        for (;pos>0;pos-=-pos&pos) {
            ret += bit[pos];
        }
        return ret;
    }
}
ll eval () {
    ll ret = 0;
    for (auto v : ord) {
        ret += BIT::qry(MAXN-2) - BIT::qry(v);
        BIT::add(v, 1);
    }
    return ret;
}
#endif
/*********************GoodLuck***********************/
int main () {
    IOS();
    srand(time(0));
    
    cin >> n;
    REP1 (i, n) {
        cin >> a[i];
    }
    for (int j=2; j<=n; j++) {
        cin >> p[j];
        edge[p[j]].emplace_back(j);
    }
    dfs(1);
    
    REP1 (i, n) {
        if (edge[i].empty()) {
#ifndef tmd
            cout << 0 << endl;
#endif
        } else {
            sort(edge[i].begin(), edge[i].end(), [&](int x, int y) {
                return
                    sum[x] < sum[y];
            });
            REP (j, SZ(edge[i])) {
#ifndef tmd
                cout << edge[i][j] << " \n"[j==SZ(edge[i])-1];
#endif
            }
        }
    }

#ifdef tmd
    pre_dfs(1);
    cout << "Sort: " << eval() << endl;
#endif
    return 0;
}