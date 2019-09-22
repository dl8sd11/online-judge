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

const int MAXN = 1000006;
const ll MOD = 1000000007;

typedef pair<ll, ll> pii;
pii pt[21];
vector<pii> slope;

bool cmp (const pii &p1, const pii &p2) {
    return p1.first * p2.second < p1.second * p2.first;
}

bool sm (const pii &p1, const pii &p2) {
    return p1.first * p2.second == p1.second * p2.first;
}

pii operator - (const pii &p1, const pii &p2) {
    pii ret = {p1.first - p2.first, p1.second - p2.second};
    if (ret.second < 0) {
        ret.first *= -1;
        ret.second *= -1;
    } else if (ret.second == 0) {
        ret.first = abs(ret.first);
    }
    return ret;
}
int ans;

bool vis[21];
pii id[21];
void check () {
    sort(slope.begin(), slope.end(), cmp);
    int cnt = 1;
    int cur = 0;
    REP1 (i, SZ(slope)) {
        if (i == SZ(slope) || !sm(slope[i], slope[i-1])) {
            cur += cnt * (cnt - 1) / 2;
            cnt = 0;
        }
        cnt++;
    }
    ans = max(ans, cur);
}

void dfs (int idx, int n) {
    if (idx == n) {
        slope.clear();
        REP (i, n) {
            slope.emplace_back(pt[id[i].first] - pt[id[i].second]);
        }
        check();
    } else {
        int f = -1;
        REP (i, n * 2) {
            if (!vis[i]) {
                f = i;
                break;
            }
        }
        assert(f != -1);
        vis[f] = true;
        for (int j=f+1; j<n*2; j++) {
            if (!vis[j]) {
                id[idx] = pii(f, j);
                vis[j] = true;
                dfs(idx+1, n);
                vis[j] = false;
            }
        }
        vis[f] = false;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n;
    cin >> n;
    REP (i, n) {
        cin >> pt[i].first >> pt[i].second;
    }

    dfs(0, n/2);

    cout << ans << endl;
    return 0;
}
