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

const int MAXN = 200005;
const ll MOD = 1000000007;

ll t, n;
ll s, l[MAXN], r[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n >> s;
        ll base = 0;
        REP (i, n) {
            cin >> l[i] >> r[i];
            base += l[i];
        }

        ll L = 0, R = MOD;
        while (L < R - 1) {
            ll mid = (L + R) >> 1;
            int cntL = 0, cntR = 0;
            vector<ll> vec;
            REP (i, n) {
                if (r[i] < mid) {
                    cntL++;
                } else if (l[i] > mid) {
                    cntR++;
                } else {
                    vec.emplace_back(l[i]);
                }
            }
            sort(vec.rbegin(), vec.rend());
            int lft = max(0LL, (n+1)/2-cntR);
            if (lft > SZ(vec)) {
                R = mid;
            } else {
                ll cur = 0;
                REP (i, lft) {
                    cur += mid - vec[i];
                }
                if (cur+base <= s) {
                    L = mid;
                } else {
                    R = mid;
                }
            }
        }
        cout << L << endl;

    }

}
