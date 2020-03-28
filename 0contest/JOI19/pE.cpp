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

const int MAXN = 2003;
const ll MOD = 1000000007;

int n, color[MAXN], m;
vector<int> edge[MAXN];

int dep[MAXN], cnt[MAXN];
bool app[MAXN];

void dfs (int nd, int par, int d) {
    dep[d] = color[nd];
    cnt[d]++;

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd, d+1);
        }
    }
}

void solve (int nd) {
    memset(cnt, 0, sizeof(cnt));
    memset(app, 0, sizeof(app));

    dfs(nd, -1, 0);
    for (int i=1; i<=n; i++) {
        if (cnt[i] == 1) {
            app[dep[i]] = true;
        }
    }

    int cnt = 0;
    for (int i=1; i<=m; i++) {
        if (app[i]) {
            cnt++;
        }
    }

    cout << cnt << endl;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    REP1 (i, n) {
        cin >> color[i];
    }

    REP1 (i, n) {
        solve(i);
    }
}
