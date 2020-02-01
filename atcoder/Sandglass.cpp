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

typedef pair<int,int> pii;
int x, k, a[MAXN], q, ans[MAXN];
pii qry[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> x;
    cin >> k;
    REP (i, k) {
        cin >> qry[i].first;
        qry[i].second = -1;
    }

    cin >> q;
    REP (i, q) {
        cin >> qry[i+k].first;
        qry[i+k].second = i;
        cin >> a[i];
    }

    sort(qry, qry+q+k);

    int L = 0, R = x, C = 0;
    int state = -1;
    REP (i, q+k) {
        int gap = qry[i].first - (i ? qry[i-1].first : 0);
        if (state < 0) {
            int mc = min(C, gap);
            C -= mc;
            gap -= mc;
            L += gap;
            L = min(x, L);
            R = max(R, L);
        } else {
            int mc =  min(x-(C+(R-L)), gap);
            C += mc;
            gap -= mc;
            R -= gap;
            C += gap;
            C = min(x, C);
            R = max(0, R);
            L = min(L, R);
        }
        debug(qry[i].first, L, R, C);

        if (qry[i].second == -1) {
            state *= -1;
        } else {
            int pos = a[qry[i].second];
            if (pos <= L) {
                ans[qry[i].second] = C;
            } else if (pos <= R) {
                ans[qry[i].second] = C + (pos - L);
            } else {
                ans[qry[i].second] = C + (R - L);
            }
        }
    }

    REP (i, q) {
        cout << ans[i] << endl;
    }
    return 0;
}
