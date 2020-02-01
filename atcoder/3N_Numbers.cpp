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
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, a[MAXN];
ll pre[MAXN], suf[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n*3) {
        cin >> a[i];
    }

    {
        // build prefix as big as possible
        priority_queue<int, vector<int>, greater<int> > pq;
        ll sum = 0;
        REP (i, n*3) {
            pq.emplace(a[i]);
            sum += a[i];
            if (SZ(pq) > n) {
                sum -= pq.top();
                pq.pop();
            }

            if (SZ(pq) == n) {
                pre[i] = sum;
            } else {
                pre[i] = -INF;
            }
        }
    }

    {
        // build prefix as small as possible
        priority_queue<int, vector<int>, less<int> > pq;
        ll sum = 0;
        for (int i=n*3-1; i>=0; i--) {
            pq.emplace(a[i]);
            sum += a[i];
            if (SZ(pq) > n) {
                sum -= pq.top();
                pq.pop();
            }

            if (SZ(pq) == n) {
                suf[i] = sum;
            } else {
                suf[i] = INF;
            }
        }
    }

    ll ans = -INF;
    REP (i, 3*n-1) {
        ans = max(ans, pre[i] - suf[i+1]);
    }

    cout << ans << endl;
    return 0;
}
