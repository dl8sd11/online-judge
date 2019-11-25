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
const int MSZ = 101;

struct Matrix {
    ll element[MSZ][MSZ];
    void operator= (const Matrix &oth) {
        REP (i, MSZ) {
            REP (j, MSZ) {
                element[i][j] = oth.element[i][j];
            }
        }
    }

    Matrix () {
        memset(element, 0, sizeof(element));
        REP (i, MSZ) {
            element[i][i] = 1;
        }
    }

    Matrix operator* (const Matrix &oth) const {
        Matrix result;
        REP (i, MSZ) {
            REP (j, MSZ) {
                result.element[i][j] = 0;
                REP (k, MSZ) {
                    result.element[i][j] += element[i][k] * oth.element[k][j];
                    result.element[i][j] %= MOD;
                }
            }
        }
        return result;
    }
} trans_matrix;

ostream& operator << (ostream& os, const Matrix &mt) {
    REP (i, MSZ) {
        REP (j, MSZ) {
            os << mt.element[i][j] << " \n"[j==MSZ-1];
        }
    }
    return os;
}

vector<ll> build_dp (vector<ll> dis, int sz) {
    vector<ll> dp(sz);
    dp[0] = 1;
    REP1 (i, sz-1) {
        dp[i] = 1;
        for (auto d : dis) {
            if (i >= d) {
                dp[i] += dp[i-d];
                dp[i] %= MOD;
            }
        }
    }

    return dp;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n, x;
    cin >> n >> x;
    vector<ll> cnt(MSZ), dp(MSZ), d(n);

    REP (i, n) {
        cin >> d[i];
        cnt[d[i]]++;
    }

    dp = build_dp(d, MSZ);
# ifdef tmd
    REP (i, MSZ) cout << dp[i] << " \n"[i==MSZ-1];
#endif

    if (x >= MSZ) {
        memset(trans_matrix.element, 0, sizeof(trans_matrix.element));
        REP1 (i, MSZ-1) {
            trans_matrix.element[i-1][0] = cnt[i];
        }
        trans_matrix.element[MSZ-1][0] = 1;
        REP1 (i, MSZ-2) {
            trans_matrix.element[i-1][i] = 1;
        }
        trans_matrix.element[MSZ-1][MSZ-1] = 1;

        debug("trans");
#ifdef tmd
        cout << trans_matrix;
#endif

        int dl = x - (MSZ-1);
        Matrix expo_matrix;
        while (dl) {
            if (dl & 1) {
                expo_matrix = expo_matrix * trans_matrix;
            }
            trans_matrix = trans_matrix * trans_matrix;
            dl >>= 1;
        }

        ll ans = 0;
        REP1 (i, MSZ) {
            ans += dp[MSZ-i] * expo_matrix.element[i-1][0];
            ans %= MOD;
        }

#ifdef tmd
        vector<ll> test_dp = build_dp(d, x+1);
        debug(test_dp[x], ans);
#endif
        cout << ans << endl;
    } else {
        cout << dp[x] << endl;
    }
}
