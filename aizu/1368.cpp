#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int MAXN = 11;
const ll MOD = 1000000007;

int tb[MAXN][MAXN];

int checker (const array<int, 5> &data) {
    int s = 0;
    REP (i, 5) {
        s = tb[s][data[i]];
    }
    return s;
}

void fll (array<int, 5> &data) {
    int e = 0;
    REP (i, 4) {
        e = tb[e][data[i]];
    }
    data[4] = e;
}

int ans;
void dfs (int idx, array<int, 5> &cur) {
    if (idx == 4) {
        fll(cur);
        assert(checker(cur) == 0);
        bool flag = false;
        REP (i, 4) {
            if (cur[i] != cur[i+1]) {
                swap(cur[i], cur[i+1]);
                flag |= checker(cur) == 0;
                swap(cur[i], cur[i+1]);
            }
        }

        REP (i, 5) {
            REP (j, 10) {
                if (j != cur[i]) {
                    int tmp = cur[i];
                    cur[i] = j;
                    flag |= checker(cur) == 0;
                    cur[i] = tmp;
                }
            }
        }

        ans += flag;
    } else {
        REP (i, 10) {
            cur[idx] = i;
            dfs(idx + 1, cur);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    REP (i, 10) {
        REP (j, 10) {
            cin >> tb[i][j];
        }
    }

    array<int, 5> cur;
    dfs(0, cur);

    cout << ans << endl;
    return 0;
}
