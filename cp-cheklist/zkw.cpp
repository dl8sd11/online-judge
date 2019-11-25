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

const int MAXN = 500005;
const ll MOD = 1000000007;

int a[MAXN*2], n, m, l, r;

void build () {
    for (int i=n-1; i>0; i--) {
        a[i] = max(a[i<<1], a[i<<1|1]);
    }
}

int qry (int L, int R) {
    int ret = -(0x3f3f3f3f);
    for (L+=n,R+=n; L<R; L>>=1, R>>=1) {
        if (L&1) {
            ret = max(ret, a[L++]);
        }
        if (R&1) {
            ret = max(ret, a[--R]);
        }
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i+n];
    }
    build();

    cin >> m;
    while (m--) {
        cin >> l >> r;
        if (l > r) {
            swap(l, r);
        }
        cout << qry(l-1, r) << endl;
    }

}
