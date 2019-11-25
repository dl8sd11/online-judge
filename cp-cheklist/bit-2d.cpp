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

const int MAXN = 2003;
const ll MOD = 1000000007;

int n, q, bit[MAXN][MAXN];

void add (int x, int y, int val) {
    for (; x<MAXN; x+=-x&x) {
        for (int yy=y; yy<MAXN; yy+=-yy&yy) {
            bit[x][yy] += val;
        }
    }
}

int qry (int x, int y) {
    int ret = 0;
    for (; x>0; x-=-x&x) {
        for (int yy=y; yy>0; yy-=-yy&yy) {
            ret += bit[x][yy];
        }
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> q;
    while (q--) {
        int cmd, xl, xr, yl, yr, val;
        cin >> cmd;
        if (cmd == 1) {
            cin >> xl >> yl >> val;
            xl++, yl++;
            add(xl, yl, val);
        } else {
            cin >> xl >> yl >> xr >> yr;
            xl++, yl++, xr++, yr++;
            debug(qry(xr, yr), qry(xr, yl-1), qry(xl-1, yr), qry(xl-1, yl-1));
            cout << qry(xr, yr) - qry(xr, yl-1) - qry(xl-1, yr) + qry(xl-1, yl-1) << endl;
        }

    }
}
