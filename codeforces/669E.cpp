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

struct Query {
    int a, t, x, id;
}query[MAXN];

map<int, int> cnt;
int n, ans[MAXN], qcnt;

void solve (int l, int r) {
    debug(l, r);
    if (l != r - 1) {
        int mid = (l + r) >> 1;
        solve(l, mid);
        solve(mid, r);

        cnt.clear();
        int lp = l, rp = mid;
        while (rp < r) {
            if (lp == mid || query[lp].t > query[rp].t) {
                if (query[rp].a == 3) {
                    debug(l, r, rp, query[rp].id, cnt[query[rp].x]);
                    ans[query[rp].id] += cnt[query[rp].x];
                }
                rp++;
            } else {
                if (query[lp].a == 1) {
                    cnt[query[lp].x]++;
                } else if (query[lp].a == 2) {
                    cnt[query[lp].x]--;
                }
                lp++;
            }
        }

        debug(l, r);
        sort(query+l, query+r, [&](Query q1, Query q2) {
            return q1.t < q2.t;
        });
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int a, t, x;
        cin >> a >> t >> x;
        query[i] = {a, t, x, qcnt};
        debug(i, qcnt);
        if (a == 3) {
            qcnt++;
        }
    }

    solve(0, n);

    REP (i, qcnt) {
        cout << ans[i] << endl;
    }
    return 0;
}
