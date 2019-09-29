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

int n, m;
int a[MAXN];

ll cur, cnt;
typedef pair<int,int> pii;
vector<pii> qry[MAXN];
void init () {
    REP1 (i, n-1) {
        if (a[i-1] < a[i]) {
            cur += a[i] - a[i-1];
        } else {
            cur += a[i] + 1;
            cnt++;
        }
        qry[a[i-1]+1].emplace_back(1, i);
        qry[a[i]+1].emplace_back(-1, i);
    }
}

int dis (int f, int t) {
    if (f < t) {
        return t - f;
    } else {
        return t + m - f;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        cin >> a[i];
    }

    init();
    ll ans = 0x3f3f3f3f3f3f3f3f;
    REP1 (i, m) {
        debug(cur, cnt);
        for (auto q : qry[i]) {
            int id = q.second;
            debug(q.first, id);
            if (q.first > 0) {
                cur++;
                cnt++;
            } else {
                cnt--;
                cur += dis(a[id-1], a[id]) -1;
                debug(dis(a[id-1], a[id]), id);
            }
        }
        cur -= cnt;
        debug(cur, cnt);
        ans = min(ans, cur);
    }

    cout << ans << endl;
    return 0;
}
