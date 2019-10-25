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

int n, m, x[MAXN];
ll dl[MAXN];

void add (int l, int r) {
    if (l > r) {
        swap(l, r);
    } else if (l == r) {
        return;
    }
    debug(l, r);
    dl[1] += r - l;
    dl[l] += l - 1;
    dl[l+1] -= l-1;
    int d = l - (r-l);
    dl[r] += d;
    dl[r+1] -= d;
    dl[l+1] += -1;
    dl[r] -= -1;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        cin >> x[i];
    }

    REP (i, m-1) {
        add(x[i], x[i+1]);
    }

    REP1 (i, n) {
        dl[i] += dl[i-1];
        cout << dl[i] << " \n"[i==n];
    }

    return 0;
}
