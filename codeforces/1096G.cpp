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

const int MAXN = 1048576*2;
const int MOD = 998244353;
const int G = 3;
int n, k;
int ans[MAXN];

int mpow (ll ba, int p) {
    int ret = 1;
    while (p) {
        if (p&1) {
            ret = ret * ba % MOD;
        }
        ba = ba * ba % MOD;
        p >>= 1;
    }
    return ret;
}

int g0[2][MAXN+1];
int a[MAXN], b[MAXN], c[MAXN];
void FFT (int *v, int n, int d) {
    for (int i=1,j=n/2; i<n-1; i++) {
        if (i < j) {
            swap(v[i], v[j]);
        }
        int ki = n / 2;
        while (ki <= j) {
            j -= ki;
            ki >>= 1;
        }
        if (j < ki) {
            j += ki;
        }
    }

    for (int h=2; h<=n; h<<=1) {
        int gx = g0[d][h];
        for (int i=0; i<n; i+=h) {
            int g = 1;
            for (int l=i; l<i+h/2; l++, g=ll(g)*gx%MOD) {
                int r = l+h/2;
                int x = v[l], y = ll(g) * v[r] % MOD;
                v[l] = x + y;
                v[r] = x - y;
                if (v[l] >= MOD) {
                    v[l] -= MOD;
                }
                if (v[r] < 0) {
                    v[r] += MOD;
                }
            }
        }
    }

    if (d) {
        int inv = mpow(n, MOD-2);
        REP (i, n) {
            v[i] = ll(v[i]) * inv % MOD;
        }
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;


    REP (i, k) {
        int d;
        cin >> d;
        b[d] = 1;
    }

    for (int h=2;h<=MAXN; h<<=1) {
        g0[0][h] = mpow(G, (MOD-1)/h);
        g0[1][h] = mpow(G, MOD-1-(MOD-1)/h);
    }

    int pw = n>>1;

    a[0] = 1;
    FFT(a, MAXN, 0);
    FFT(b, MAXN, 0);
    while (pw) {
        if (pw & 1) {
            REP (i, MAXN) {
                a[i] = ll(a[i]) * b[i] % MOD;
            }
        }
        REP (i, MAXN) {
            b[i] = ll(b[i]) * b[i] % MOD;
        }
        pw >>= 1;
    }
    FFT(a, MAXN, 1);

    ll ret = 0;
    REP (i, MAXN) {
        (ret += a[i] * ll(a[i])) %= MOD;
    }

    cout << ret << endl;
    return 0;
}


