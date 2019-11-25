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

const int MAXN = 1024;
const int MOD = 1000000009;

int n, m, K, dp[2][MAXN][MAXN], p[MAXN], q[MAXN], pr[2][2][MAXN][MAXN];
pair<int,int> rng[2][MAXN];
// int dp2[2][MAXN][MAXN];

void add (int &x, int val) {
    x += val;
    if (x >= MOD) {
        x-= MOD;
    }
}

void sub (int &x, int val) {
    x -= val;
    if (x < 0) {
        x+= MOD;
    }
}

int sub2 (int x, int y) {
    x -= y;
    if (x < 0) {
        x += MOD;
    }
    return x;
}

void trim (pair<int,int> &rg, int r) {
    rg.second = min(rg.second, r);
    if (rg.first > rg.second) {
        rg.first = rg.second + 1;
    }
}

ostream& operator << (ostream &os, pair<int,int> pa) {
    return os << pa.first << ' ' << pa.second;
}
/*********************GoodLuck***********************/
int main () {
#ifndef tmd
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
#endif

    IOS();
    cin >> n >> m >> K;
    REP1 (i, n) {
        cin >> p[i];
    }
    REP1 (i, m) {
        cin >> q[i];
    }
    sort(p+1, p+n+1);
    sort(q+1, q+1+m);

    REP1 (i, n) {
        rng[0][i] = {1, lower_bound(q+1,q+m+1, p[i])-q-1};
    }
    REP1 (i, m) {
        rng[1][i] = {upper_bound(p+1,p+1+n, q[i])-p, n};
    }


#define cdp dp[ch&1]
#define pdp dp[(ch&1)^1]
// #define cdp2 dp2[ch&1]
// #define pdp2 dp2[(ch&1)^1]
#define cpr pr[ch&1]
#define ppr pr[(ch&1)^1]

    REP (i, n+1) {
        REP (j, m+1) {
            dp[0][i][j] = 1;
            // dp2[0][i][j] = 1;
            if (i) {
                pr[0][0][i][j] = pr[0][0][i-1][j];
            }
            if (j) {
                pr[0][1][i][j] = pr[0][1][i][j-1];
            }
            if (i*j != 0) {
                add(pr[0][0][i][j], dp[0][i-1][j-1]);
                add(pr[0][1][i][j], dp[0][i-1][j-1]);
            }
        }
    }

    debug(pr[0][0][2][1], pr[0][0][2][0]);
    debug(pr[0][1][2][1], pr[0][1][1][1]);
    debug(dp[0][1][0]);

    REP1 (ch, K) {
        REP (i, n+1) {
            cdp[i][0] = 0;
        }
        REP (j, m+1) {
            cdp[0][j] = 0;
        }
        REP1 (i, n) {
            REP1 (j, m) {
                cdp[i][j] = cdp[i-1][j-1];

#ifdef tmdd
                cdp2[i][j] = cdp2[i-1][j-1];
                for (int k=0; k<j; k++) {
                    if (p[i] > q[k]) {
                        add(cdp2[i][j], pdp2[i-1][k-1]);
                    }
                }
                for (int k=0; k<i; k++) {
                    if (p[k] > q[j]) {
                        add(cdp2[i][j], pdp2[k-1][j-1]);
                    }
                }
                if (p[i] > q[j]) {
                    add(cdp2[i][j], pdp2[i-1][j-1]);
                }
                debug(ch, i, j, cdp2[i][j]);
#endif

                pair<int,int> prng = rng[0][i], qrng = rng[1][j];
                trim(prng, j);
                trim(qrng, i);


                add(cdp[i][j], sub2(ppr[1][i][prng.second], ppr[1][i][prng.first-1]));
                debug(cdp[i][j]);
                add(cdp[i][j], sub2(ppr[0][qrng.second][j], ppr[0][qrng.first-1][j]));
                debug(cdp[i][j]);
                if (p[i] > q[j]) {
                    sub(cdp[i][j], pdp[i-1][j-1]);
                }
                debug(prng, qrng, cdp[i][j]);
//                assert(cdp[i][j] == cdp2[i][j]);

                cpr[1][i][j] = cpr[1][i][j-1];
                cpr[0][i][j] = cpr[0][i-1][j];
                add(cpr[0][i][j], cdp[i-1][j-1]);
                add(cpr[1][i][j], cdp[i-1][j-1]);
            }
        }
    }

    cout << dp[K&1][n][m] << endl;

}
