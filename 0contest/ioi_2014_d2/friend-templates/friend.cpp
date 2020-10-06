#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define first X
#define second Y
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream &__printRng (ostream& os, IT bg, IT ed) {
    for (IT it=bg; it!=ed; it++) {
        if (it == bg) os << "{" << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream &operator << (ostream& os, const vector<T> &vec) {
    return __printRng(os,ALL(vec));
}
#else
#define debug(...)
#endif
#include "friend.h"

// Find out best sample

const int MAXN = 1003;
vector<int> edge[MAXN];
bool g[MAXN][MAXN];
void add_edge (int u, int v) {
    edge[u].eb(v);
    edge[v].eb(u);
    g[u][v] = true;
    g[v][u] = true;
}

bool vis[MAXN];


vector<int> xs, ys;
void dfs (int nd, int c) { 
    if (c) xs.eb(nd);
    else ys.eb(nd);
    vis[nd] = true;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            dfs(v, c^1);
        }
    }
}

int yp[MAXN];
bool mat (int nd) {
    if (vis[nd]) return false;
    vis[nd] = true;
    for (int u : edge[nd]) {
        if (yp[u] == -1 || mat(yp[u])) {
            yp[u] = nd;
            return true;
        }
    }
    return false;
}


int findSample(int n,int confidence[],int host[],int p[]){
    bool fc = false;
    for (int i=1; i<n; i++) {
        if (p[i] == 0) {
            add_edge(i, host[i]);
        } else if (p[i] == 1) {
            for (auto v : edge[host[i]]) {
                add_edge(v, i);
            }
        } else {
            for (auto v : edge[host[i]]) {
                add_edge(v, i);
            }
            add_edge(i, host[i]);
            fc = true;
        }
    }

    int ans = 0;
    for (int i=0; i<(1<<n); i++) {
        bool idp = true;
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                if (((i>>j)&1) && ((i>>k)&1) && g[j][k] != 0) {
                    idp = false;
                    break;
                }
            }
        }
        if (!idp) continue;
        int cur = 0;
        for (int j=0; j<n; j++) {
            if ((i>>j) & 1) {
                cur += confidence[j];
            }
        }
        ans = max(ans, cur);
    }


    return ans;

}
