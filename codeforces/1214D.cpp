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

int n, m;
bool rab[MAXN], rba[MAXN], bk[MAXN];

int id (int x, int y) {
    return x*m + y;
}

map<int, int> mp;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        REP (j, m) {
            char c;
            cin >> c;
            bk[id(i, j)] = c == '#';
        }
    }

    int ans = 2;
    rab[id(n-1, m-1)] = true;
    for (int i=n-1; i>=0; i--) {
        for (int j=m-1; j>=0; j--) {
            if (i + j != n+m-2) {
                if (!bk[id(i, j)]) {
                    if ((i != n-1 && rab[id(i+1,j)]) || (j != m-1 && rab[id(i, j+1)])) {
                        rab[id(i, j)] = true;
                    }
                }
            }
        }
    }

    rba[0] = true;
    REP (i, n) {
        REP (j, m) {
            if (i + j != 0) {
                if (!bk[id(i, j)]) {
                    if ((i != 0 && rba[id(i-1,j)]) || (j != 0 && rba[id(i, j-1)])) {
                        rba[id(i, j)] = true;
                    }
                }
            }
        }
    }

    REP (i, n) {
        REP (j, m) {
            if (rab[id(i, j)] && rba[id(i, j)]) {
                mp[i+j]++;
            }
        }
    }
    REP1 (i, n+m-3) {
        if (mp[i] == 1) {
            ans = min(ans, 1);
        } else if (mp[i] == 0) {
            ans = 0;
        }
    }

    cout << ans*(rab[0]) << endl;
    return 0;
}
