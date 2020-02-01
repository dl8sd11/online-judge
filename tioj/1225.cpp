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

int n, a[MAXN], l[MAXN], r[MAXN];
ll ans;
bool vis[MAXN];

typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > pq;

int calc (int i) {
    int mn = MOD;
    if (a[l[i]] >= a[i]) {
        mn = min(mn, a[l[i]]);
    }
    if (a[r[i]] >= a[i]) {
        mn = min(mn, a[r[i]]);
    }
    return mn;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    a[0] = a[n+1] = -1;
    REP1 (i, n) {
        cin >> a[i];
        l[i] = i-1;
        r[i] = i+1;
    }
    #ifdef tmd
    REP1 (i, n) {
        debug(a[i], l[i], r[i], calc(i));
    }
    #endif

    REP1 (i, n) {
        int mn = calc(i);
        if (mn != MOD) {
            debug(mn, i);
            pq.emplace(mn, i);
        }
    }

    REP (i, n-1) {
        int fnd = -1;
        int val = -1;
        while (pq.size()) {
            fnd = pq.top().second;
            val = pq.top().first;
            if (!vis[fnd] && pq.top().first == calc(fnd)) {
                break;
            }
            pq.pop();
        }
        vis[fnd] = true;
        debug(fnd, val);

        ans += val;
        int L = l[fnd], R = r[fnd];
        r[L] = R;
        l[R] = L;
        if (L != 0) {
            pq.emplace(calc(L), L);
        }
        if (R != n+1) {
            pq.emplace(calc(R), R);
        }
    }

    cout << ans << endl;
    return 0;
}
