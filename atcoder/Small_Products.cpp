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

int n, k;
ll pre[102][MAXN];
vector<int> l, r, mt;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    for (int i=1,j; i<=n; i=j+1) {
        j = n/(n/i);
        l.emplace_back(i);
        r.emplace_back(j);
    }

    REP (i, SZ(l)) {
        int idx = lower_bound(r.begin(), r.end(), n/l[i]) - r.begin();
        assert(r[idx] == n/l[i]);
        mt.emplace_back(idx);
        debug(l[i], r[i], idx);
    }

    int bk = SZ(mt);

    REP (i, bk) {
        pre[0][i] = 1;
    }

    REP1 (i, k) {
        REP (j, bk) {
            pre[i][j] = j ? pre[i][j-1] : 0;
            pre[i][j] += pre[i-1][mt[j]] * (r[j]-l[j]+1) % MOD;
            pre[i][j] %= MOD;
            //debug(i, j, pre[i-1][mt[j]] * (r[j]-l[j]+1));
        }
    }

    cout << pre[k][bk-1] << endl;
    return 0;
}
