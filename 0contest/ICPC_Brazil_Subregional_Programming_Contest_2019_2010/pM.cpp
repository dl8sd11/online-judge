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
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;

ll n, c, t, p[MAXN];
/****GOOD_LUCK****/
int main () {
    IOS();

    cin >> n >> c >> t;
    REP (i, n) {
        cin >> p[i];
    }

    ll l = 0, r = 1000000007;
    while (l < r - 1) {
        ll mid = (l + r) >> 1;
        bool valid;
        {
            int j = 0;
            for (int i=0; i<c; i++) {
                int sum = 0;
                while (j<n && sum+p[j]<=mid*t) {
                    sum += p[j];
                    j++;
                }
            }
            valid = j == n;
        }

        if (valid) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << r << endl;
    return 0;
}
