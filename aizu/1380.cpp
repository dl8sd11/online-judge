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
const ll INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<int, int> pii;

int n, t;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> t;
    int sum = 0;
    int mx = 0;
    REP (i, n) {
        int d;
        cin >> d;
        mx = max(mx, d);

        if (t < sum) {
            cout << 1 << endl;
        } else {
            int rem = (t - sum) % mx;
            if (rem >= d) {
                cout << (t - sum) / mx + 2 << endl;
            } else {
                cout << (t - sum) / mx + 1 << endl;
            }
        }

        if (sum < t) {
            sum += d;
        }
    }

    return 0;
}
