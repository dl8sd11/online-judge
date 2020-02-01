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

const int MAXN = 10004;
const ll MOD = 1000000007;

int n, a[MAXN];
bool l[MAXN], r[MAXN], lm[MAXN], rm[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;
    vector<int> b;
    REP (i, n) {
        cin >> a[i];
        b.emplace_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end())-b.begin());
    REP (i, n) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        debug(a[i]);
    }

    int ans = 0;
    REP (i, n-1) {
        int len = 1;
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(lm, 0, sizeof(lm));
        memset(rm, 0, sizeof(rm));
        int lc = 0, rc = 0;
        while (i-len+1>=0 && i+len<n) {
            int LV = a[i-len+1];
            int RV = a[i+len];
            l[LV] = true;
            r[RV] = true;
            if (rm[LV] == 1) {
                rm[LV] = false;
                rc--;
            }
            if (lm[RV] == 1) {
                lm[RV] = false;
                lc--;
            }
            if (r[LV] == 0) {
                if (!lm[LV]) {
                    lc++;
                }
                lm[LV] = true;
            }
            if (l[RV] == 0) {
                if (!rm[RV]) {
                    rc++;
                }
                rm[RV] = true;
            }
            if (lc == 0 && rc == 0) {
                ans = max(ans, len*2);
            }


            len++;
        }
    }

    cout << ans << endl;
    return 0;
}
