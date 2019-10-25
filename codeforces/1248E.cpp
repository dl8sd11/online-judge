#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmdd
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


ll n, p;
queue<ll> que;
ll bst, ans[MAXN], t[MAXN];
vector<pii> tsrt;
set<ll> leave_id, ready_id;
priority_queue<ll, vector<ll>, greater<ll> > tim;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> p;
    REP (i, n) {
        cin >> t[i];
        tim.emplace(t[i]);
        tsrt.emplace_back(t[i], i);
    }
    sort(tsrt.begin(), tsrt.end());

    ll lst = -1;
    bst = -p;
    while (tim.size()) {
        ll cur = tim.top();
        tim.pop();
        if (cur <= lst) {
            continue;
        }
        lst = cur;

        if (SZ(que) && cur - bst >= p) {
            ans[que.front()] = cur;
            leave_id.erase(que.front());
            que.pop();
        }

        auto l = lower_bound(tsrt.begin(), tsrt.end(), pii(cur, -1));
        auto r = lower_bound(tsrt.begin(), tsrt.end(), pii(cur+1, -1));

        for (auto it=l; it!=r; it++) {
            ready_id.insert(it->second);
        }

        ll mn = leave_id.empty() ? n + 1 : (*leave_id.begin());

        if (ready_id.size() && (*ready_id.begin()) < mn) {
            ll nw = *ready_id.begin();
            ready_id.erase(ready_id.begin());
            leave_id.insert(nw);
            que.push(nw);
        }

        if (!que.empty() && cur - bst >= p) {
            bst = cur;
            tim.emplace(cur+p);
            debug(cur+p, que.front());
        }
    }

    REP (i, n) {
        cout << ans[i] << " \n"[i==n-1];
    }

}
