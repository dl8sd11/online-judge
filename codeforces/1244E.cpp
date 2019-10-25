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

int n, a[MAXN], l, r;
ll k;

void upd () {
    while (l<n-1 && a[l] == a[l+1]) {
        l++;
    }
    while (r>0 && a[r] == a[r-1]) {
        r--;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
    }
    sort(a, a+n);

    l = 0, r = n-1;
    upd();
    while (l < r) {
        if (l+1 < n-r) {
            ll stp = k / (l + 1);
            if (stp == 0) {
                break;
            }
            stp = min(stp, ll(a[l+1] - a[l]));
            a[l] += stp;
            k -= stp * (l+1);
        } else {
            ll stp = k / (n-r);
            if (stp == 0) {
                break;
            }
            stp = min(stp, ll(a[r] - a[r-1]));
            a[r] -= stp;
            k -= stp * (n-r);
        }
        debug(l, r);
        #ifdef tmd
        REP (i, n) {
            cout << a[i] << " \n"[i==n-1];
        }
        #endif
        upd();
    }

    cout << (l >= r ? 0 : a[r] - a[l]) << endl;
    return 0;
}

