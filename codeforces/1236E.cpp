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

int n, m, a[MAXN], bitl[MAXN], bitr[MAXN];

void add (int x, int val, int *bit) {
    for (; x<MAXN; x+=-x&x) {
        bit[x] += val;
    }
}

int qry(int x, int *bit) {
    int ret = 0;
    for (;x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int lbd (int x, int *bit) {
    int l = 0, r = n + 1;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (qry(mid, bit) >= x) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}

int ubd (int x, int *bit) {
    return lbd(x+1, bit);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    REP1 (i, n) {
        add(i, 1, bitl);
        add(i, 1, bitr);
    }

    REP1 (i, m) {
        debug(i);
        cin >> a[i];
        int l = lbd(a[i]+1, bitl), r = ubd(a[i]+1, bitl);
        add(1, -1, bitl);
        add(l, 1, bitl);
        add(r, -1, bitl);

        l = lbd(a[i]-1, bitr), r = ubd(a[i]-1, bitr);
        add(1, 1, bitr);
        add(l, -1, bitr);
        add(r, 1, bitr);
    }

    ll ans = 0;
    if (n != 1) {
        REP1 (i, n) {
            int l = qry(i, bitl), r = qry(i, bitr);
            l = max(1, l-1), r = min(n, r+1);
            debug(l, r);
            ans += r - l + 1;
        }
    }

    cout << ans << endl;
}
