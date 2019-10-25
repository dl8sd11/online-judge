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

const int MAXN = 500005;
const ll MOD = 1000000007;

int n, m, ch[MAXN], ans[MAXN];
int dep[MAXN];
vector<int> edge[MAXN];
vector<pair<int,int> > qry[MAXN];

void dfs (int nd, int d=1) {
    for (auto Q : qry[nd]) {
        ans[Q.second] ^= dep[Q.first];
    }

    for (auto v : edge[nd]) {
        dfs(v, d+1);
    }
    dep[d] ^= (1<<ch[nd]);

    for (auto Q : qry[nd]) {
        ans[Q.second] ^= dep[Q.first];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n-1) {
        int p;
        cin >> p;
        edge[p].emplace_back(i+2);
    }
    REP1 (i, n) {
        char c;
        cin >> c;
        ch[i] = c - 'a';
    }

    REP (i, m) {
        int v, d;
        cin >> v >> d;
        qry[v].emplace_back(d, i);
    }

    dfs(1, 1);

    REP (i, m) {
        cout << (ans[i]&(ans[i]-1) ? "No" : "Yes") << endl;
    }

}
