#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif


const int MAXN = 5005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, k;
int a[MAXN], b[MAXN], c[MAXN], lst[MAXN];
int rem[MAXN];

bool test (int start, int init) {
    for (int i=start;i<=n; i++) {
        if (init < a[i]) {
            return false;
        }
        init += b[i];
    }
    return true;
}
void build_rem () {
    int sum = k;
    for (int i=1; i<=n; i++) {
        sum += b[i];
        int L = 0, R = sum + 1;
        while (L < R - 1) {
            int mid = (L + R) >> 1;
            if (test(i+1, sum-mid)) {
                L = mid;
            } else {
                R = mid;
            }
        }
        sum -= L;
        rem[i] = L;
    }
}

struct Item {
    int cost, val;
};
vector<Item> items;

int dp[MAXN*2][MAXN];

vector<int> redg[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m >> k;

    REP1 (i, n) {
        cin >> a[i] >> b[i] >> c[i];
        lst[i] = i;
    }

    REP (i, m) {
        int f, t;
        cin >> f >> t;
        lst[t] = max(lst[t], f);
    }
    REP1 (i, n) {
        redg[lst[i]].emplace_back(i);
    }

    if (!test(1, k)) {
        cout << -1 << endl;
    } else {
        build_rem();
        pary(rem+1, rem+1+n);
        REP1 (i, n) {
            items.push_back({-rem[i], 0});
            for (auto v : redg[i]) {
                items.push_back({1, c[v]});
            }
        }

        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0;

        int ans = 0;
        REP1 (i, SZ(items)) {
            Item cur = items[i-1];
            debug(cur.cost, cur.val);
            for (int j=0;j<MAXN;j++) {
                if (j+cur.cost >= 0 && j+cur.cost < MAXN && dp[i-1][j+cur.cost] >= 0) {
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j+cur.cost]+cur.val);
                } else {
                    dp[i][j] = dp[i-1][j];
                }

                ans = max(ans, dp[i][j]);
            }
        }

        cout << ans << endl;
    }

}
