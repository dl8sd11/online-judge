#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define eb emplace_back
#define MEM(i,a) memset(i, (a), sizeof(i))
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

int n, ans;
vector<vector<int> > edge;
vector<int> s, dp;

void dfs (int nd, int par) {
    int lf = 0;
    int bst = 0, sum = 0;
    for (int u : edge[nd]) {
        if (u != par) {
            lf++;
            dfs(u, nd);
            bst = max(bst, dp[u]);
            sum += dp[u];
        }
    }

    if (lf == 0) {
        dp[nd] = s[nd];
        ans = max(ans, dp[nd]);
    } else {
        dp[nd] = max(s[nd], sum - s[nd]);        
        ans = max({ans, s[nd] + bst, sum - s[nd]});
    }
}


int main () {
    IOS();
    cin >> n;
    edge.resize(n);
    dp.resize(n);
    s.resize(n);
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        u--,v--;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    for (int i=0; i<n; i++) {
        char c;
        cin >> c;
        s[i] = c == '1';
    }
    dfs(0, 0);

    cout << ans << endl;
}
