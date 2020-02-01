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
const int MAXB = 60;

int n;
ll a[MAXN], sum, mk, fmask[MAXB];

void ins (ll val) {
    for (int i=MAXB-1; i>=0; i--) {
        if ((val & (1LL<<i)) == 0) {
            continue;
        }
        if (fmask[i] == 0) {
            fmask[i] = val;
            return;
        }

        val ^= fmask[i];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i];
        sum ^= a[i];
    }

    mk = sum ^ ((1LL<<MAXB) - 1);
    REP (i, n) {
        ins(a[i] & mk);
    }

    ll res = 0;
    for (int i=MAXB-1; i>=0; i--) {
        if ((res & (1LL<<i)) == 0) {
            res ^= fmask[i];
        }
    }

    debug(res, sum);
    cout << res*2 + sum << endl;

}
