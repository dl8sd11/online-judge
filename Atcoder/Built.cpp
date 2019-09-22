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

const int MAXN = 100005;
const ll MOD = 1000000007;

typedef pair<int, int> pii;

int n, djs[MAXN];
pii pt[MAXN];
map<int, vector<int> > x, y;

struct Plan {
    int u, v, cost;
    bool operator < (const Plan &p) {
        return cost < p.cost;
    }
};
vector<Plan> plan;

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

bool mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return false;
    }
    djs[x] = y;
    return true;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;

    REP (i, n) {
        djs[i] = i;
    }

    REP (i, n) {
        cin >> pt[i].first >> pt[i].second;
        x[pt[i].first].emplace_back(i);
        y[pt[i].second].emplace_back(i);
    }

    ll ans = 0;
    for (auto it=x.begin(); it!=x.end(); it++) {
        if (it !=x.begin()) {
            plan.push_back({*(it->second.begin()), *(prev(it)->second.begin()), it->first - prev(it)->first});
        }
        const auto &v = it->second;
        REP (i, SZ(v) - 1) {
            mrg(v[i], v[i+1]);
        }
    }

    for (auto it=y.begin(); it!=y.end(); it++) {
        if (it !=y.begin()) {
            plan.push_back({*(it->second.begin()), *(prev(it)->second.begin()), it->first - prev(it)->first});
        }
        const auto &v = it->second;
        REP (i, SZ(v) - 1) {
            mrg(v[i], v[i+1]);
        }
    }

    sort(plan.begin(), plan.end());

    for (const auto &p : plan) {
        if (mrg(p.u, p.v)) {
            ans += p.cost;
        }
    }

    cout << ans << endl;
    return 0;
}
