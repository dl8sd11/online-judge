#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> pii;
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream& printRng (ostream& os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        if (it == bg) os << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream& operator << (ostream& os, const vector<T>& v) {return printRng(os,ALL(v));}
template<typename T, typename S> ostream& operator << (ostream& os, const map<T,S>& v) {return printRng(os,ALL(v));}
template<typename T, typename S> ostream& operator << (ostream& os, const pair<T,S>& v) {return os<<"("<<v.X<<","<<v.Y<<")";}
#else
#define debug(...)
#endif
#include "race.h"

int n, k;
vector<vector<pii> > edge;
vector<ll> dep;
vector<int> edp;
vector<map<ll,int> > dmp;

const int INF = 0x3f3f3f3f;

int getm (map<ll,int> &mp, ll tg) {
    auto ptr = mp.find(tg);
    if (ptr == mp.end()) return INF;
    else return ptr->Y;
}

int ans = INF;
void dfs (int nd, int par) {
    dmp[nd][dep[nd]] = edp[nd];
    for (auto &[u, w] : edge[nd]) {
        if (u != par) {
            dep[u] = dep[nd] + w;
            edp[u] = edp[nd] + 1;
            dfs(u, nd);

            if (SZ(dmp[nd]) < SZ(dmp[u])) {
                swap(dmp[nd], dmp[u]);
            }

            debug(dmp[nd]);
            for (auto &[dw, de] : dmp[u]) {
                ll rem = k - (dw-dep[nd]) + dep[nd];
                int res = getm(dmp[nd], rem);
                debug(nd, u, de, res, edp[nd]);
                ans = min(ans, de + res - 2*edp[nd]);
            }

            for (auto &[dw, de] : dmp[u]) {
                if (dmp[nd].count(dw)) {
                    int &x = dmp[nd][dw];
                    x = min(x, de);
                } else {
                    dmp[nd][dw] = de;
                }
            }
        }
    }
    debug(nd, dmp[nd]);
}
int best_path(int N, int K, int H[][2], int L[]) {
    n = N;
    k = K;
    edge.resize(N);
    for (int i=0; i<n-1; i++) {
        int u, v, w;
        u = H[i][0];
        v = H[i][1];
        w = L[i];
        edge[u].eb(v, w);
        edge[v].eb(u, w);
    }
    dep.resize(n);
    edp.resize(n);
    dmp.resize(n);
    dfs(0, -1);
    return ans <= n ? ans : -1;
}

