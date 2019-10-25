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

const int MAXN = 7003;
const ll MOD = 1000000007;

int n, cnt[MAXN], res;
ll a[MAXN], b[MAXN];
vector<int> rev[MAXN];
bool ban[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i];
    }
    REP (i, n) {
        cin >> b[i];
    }

    REP (i, n) {
        REP (j, n) {
            if (a[i] & (a[i]^a[j])) {
                cnt[i]++;
                rev[j].emplace_back(i);
            }
        }
    }

    int deg = n-1;
    REP (u, n) {
        REP (i, n) {
            if (cnt[i] == deg) {
                debug(i, cnt[i]);
                ban[i] = true;
                for (auto v : rev[i]) {
                    cnt[v]--;
                }
                deg--;
                break;
            }
        }
    }

    ll cur = 0;
    REP (i, n) {
        if (!ban[i]) {
            res++;
            cur += b[i];
        }
    }

    cout << (res >= 2 ? cur : 0) << endl;
    return 0;
}
