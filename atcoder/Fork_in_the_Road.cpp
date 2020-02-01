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

const int MAXN = 602;
const ll MOD = 1000000007;

struct Edge {
    int des, nxt;
} edge[MAXN*MAXN];
int head[MAXN], ecnt;

int n, m;
double dp[MAXN];

double ans;
void calc (int ban) {
    for (int i=n-1; i>=1; i--) {
        dp[i] = 0;
        int cnt = 0;
        for (int id=head[i]; id!=-1; id=edge[id].nxt) {
            if (id == ban) {
                continue;
            }
            dp[i] += dp[edge[id].des] + 1;
            cnt++;
        }
        dp[i] /= cnt;
    }
    if (dp[1] != 0) {
        ans = min(ans, dp[1]);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m;

    memset(head, -1, sizeof(head));
    REP (i, m) {
        int f, t;
        cin >> f >> t;
        edge[ecnt++] = {t, head[f]};
        head[f] = ecnt - 1;
    }

    ans = n + 3;
    calc(-1);

    vector<int> ban;
    REP1 (i, n-1) {
        int mx = -1;
        double val = -1;
        for (int id=head[i]; id!=-1; id=edge[id].nxt) {
            if (dp[edge[id].des] > val) {
                mx = id;
                val = dp[edge[id].des];
            }
        }
        ban.emplace_back(mx);
    }

    for (auto b : ban) {
        calc(b);
    }

    cout << fixed << setprecision(10) << ans << endl;
}
