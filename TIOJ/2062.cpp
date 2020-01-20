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


const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

// 8: 27 ~ 8:33
int n, m, vis[MAXN];
bool isBi = true;
vector<int> p[2];
vector<int> edge[MAXN];

void dfs (int nd, int tag) {
    vis[nd] = tag;
    p[tag-1].emplace_back(nd);
    for (auto v : edge[nd]) {
        if (vis[v] == 0) {
            dfs(v, 3-tag);
        } else {
            if (vis[v] + tag != 3) {
                isBi = false;
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    REP1 (i, n) {
        if (vis[i] == 0) {
            dfs(i, 1);
        }
    }

    if (isBi) {
        cout << SZ(p[0]) << " " << SZ(p[1]) << endl;
        REP (u, 2) {
            REP (i, SZ(p[u])) {
                cout << p[u][i] << " \n"[i==SZ(p[u])-1];
            }
        }
    } else {
        cout << -1 << endl;
    }

}
