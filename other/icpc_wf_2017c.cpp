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

const int MAXN = 102;
const ll MOD = 1000000007;

int n, m;
int g[MAXN][MAXN];
int r[MAXN], c[MAXN];
vector<int> edge[MAXN];

bool vis[MAXN];
int yp[MAXN], xp[MAXN];
bool dfs (int nd) {
    if (vis[nd]) {
        return false;
    }
    vis[nd] = true;
    for (auto v : edge[nd]) {
        if (yp[v] == -1 || dfs(v)) {
            yp[v] = nd;
            xp[nd] = v;
            return true;
        }
    }
    return false;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    ll sum = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> g[i][j];
            sum += max(g[i][j]-1, 0);
            r[i] = max(r[i], g[i][j]);
            c[j] = max(c[j], g[i][j]);
        }
    }
    pary(r, r+n);
    pary(c, c+m);

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (r[i] == c[j] && r[i] != 0 && g[i][j] != 0) {
                edge[i].eb(j);
            }
        }
    }

    memset(yp, -1, sizeof(yp));
    for (int i=0; i<n; i++) {
        memset(vis, 0, sizeof(vis));
        dfs(i);
    }

    for (int i=0; i<n; i++) {
        sum -= max(0, r[i] - 1);
    }
    for (int j=0; j<m; j++) {
        if (yp[j] == -1) {
            sum -= max(0, c[j] - 1);
        }
    }

    cout << sum<< endl;
}

