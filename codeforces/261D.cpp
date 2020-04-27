#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx", "avx2", "fma")
#include <iostream>
#include <cstring>
#include <set>
using namespace std;

#define MX(a,b) a=a>b?a:b;
const int MAXN = 100005;

int k, n, B, t, b[MAXN];

struct BIT {
    int bit[MAXN], org[MAXN];
    void clr () {
        memset(bit, 0, sizeof(bit));
        memset(org, 0, sizeof(bit));
    }

    void upd (int x, int v) {
        if (org[x] < v) {
            org[x] = v;
            for (;x<MAXN; x+=-x&x) {
                MX(bit[x], v);
            }
        }        
    }

    int qry (int x) {
        int ret = 0;
        for (;x>0; x-=-x&x) {
            MX(ret, bit[x]);
        }
        return ret;
    }
} rmq;

int len[MAXN], mn[MAXN];
int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> k >> n >> B >> t;
    B++;

    while (k--) {
        for (int i=0; i<n; i++) {
            cin >> b[i];
        }

        if (t >= min(B, n)) {
            set<int> res;
            for (int i=0; i<n; i++) {
                res.insert(b[i]);
            }
            cout << res.size() << endl;
            continue;
        }

        rmq.clr();

        int ans = 0;

        memset(len, 0, sizeof(len));
        memset(mn, 0x3f, sizeof(mn));
        for (int i=0; i<t; i++) {
            for (int j=0; j<n; j++) {
                int d = b[j];
                while(mn[len[j]] < d) {
                    len[j]++;
                }
                mn[len[j]] = d;
                ans = max(ans, len[j]+1);
            }
        }
        /*
        for (int i=0; i<n*t; i++) {
            int a = b[i%n];
            int cur = rmq.qry(a-1);
            rmq.upd(a, cur+1);
            MX(ans, cur+1);
        }
        */

        cout << ans << endl;


    }

    return 0;
}
