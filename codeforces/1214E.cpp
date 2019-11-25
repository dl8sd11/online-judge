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

int n;
vector<pair<int,int> > d, ans;
vector<int> node[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int v;
        cin >> v;
        d.emplace_back(v, i+1);
    }

    sort(d.rbegin(), d.rend());
    REP1 (i, SZ(d) - 1) {
        ans.emplace_back(d[i-1].second*2-1,d[i].second*2-1);
    }

    int rt = d.front().first - 1;
    node[0].emplace_back(d[rt].second*2-1);

    REP (i, SZ(d)) {
        int cur = d[i].second<<1;
        int dep = d[i].first - abs(i - rt);
        if (dep <= 0) {
            if (i + d[i].first - 1 < SZ(d)) {
                ans.emplace_back(d[i+d[i].first-1].second*2-1, cur);
            } else {
                ans.emplace_back(d[i-d[i].first+1].second*2-1, cur);
            }
        } else {
            ans.emplace_back(node[dep-1].front(), cur);
            node[dep].emplace_back(cur);
        }
    }

    for (auto p : ans) {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
