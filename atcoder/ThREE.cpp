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

int n;
vector<int> edge[MAXN];

int ans[MAXN];
vector<int> x[MAXN];
void dfs (int nd, int par, bool c) {
    x[c].eb(nd);

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd, !c);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1, -1, 0);
    if (x[0].size() >= x[1].size()) {
        swap(x[0], x[1]);
    }

    int oc = n / 3;
    debug(oc, x[0].size(), x[1].size());
    if (x[0].size() <= oc) {
        int c = 3;
        for (auto v : x[0]) {
            ans[v] = c;
            c += 3;
        }
    } else {
        for (int i=0; i*3+1<=n; i++) {
            ans[x[0][i]] = i*3+1;
        }
        for (int j=0; j*3+2<=n; j++) {
            ans[x[1][j]] = j*3+2;
        }
    }

    set<int> x;
    for (int i=1;i<=n;i++) {
        x.insert(i);
    }
    for (int i=1; i<=n; i++) {
        if (ans[i]) {
            x.erase(ans[i]);
        }
    }
    for (int i=1; i<=n; i++) {
        if (ans[i] == 0) {
            ans[i] = *x.begin();
            x.erase(x.begin());
        }
    }

    REP1 (i, n) {
        cout << ans[i] << " \n"[i==n];
    }
}
