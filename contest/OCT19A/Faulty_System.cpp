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

const int MAXN = 21;
const ll MOD = 1000000007;

int t;
int n, m;
vector<pair<int,int> > edg1, edg2;

int djs[MAXN];
int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void uni (int x, int y) {
    x = fnd(x), y = fnd(y);
    djs[x] = y;
}

bool cho[MAXN];
bool check (vector<pair<int ,int>> &edg) {
    REP1 (i, n) {
        djs[i] = i;
    }
    REP (i, m) {
        if (cho[i]) {
            uni(edg[i].first, edg[i].second);
        }
    }
    REP1 (i, n) {
        if (fnd(i) != fnd(1)) {
            return false;
        }
    }
    return true;
}

int ans;
void dfs (int idx) {
    if (idx == m) {
        int cnt = 0;
        REP (i, m) {
            cnt += cho[i];
        }
        if (check(edg1) && check(edg2)) {
            ans = min(ans, cnt);
        }
    } else {
        cho[idx] = false;
        dfs(idx + 1);
        cho[idx] = true;
        dfs(idx + 1);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n >> m;
        edg1.clear();
        edg2.clear();
        REP (i, m) {
            int u, v;
            cin >> u >> v;
            edg1.emplace_back(u, v);
        }

        REP (i, m) {
            int u, v;
            cin >> u >> v;
            edg2.emplace_back(u, v);
        }

        ans = m;
        dfs(0);

        cout << ans << endl;
    }
    return 0;
}
