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

const int MAXN = 1<<19;
const ll MOD = 1000000007;

typedef complex<double> cd;

int n, m, k;
string s, t;
cd omg[MAXN + 1], a[MAXN], b[MAXN], c[MAXN];
int sum[MAXN];

void FFT (cd *v, bool inverse) {
    for (int i=1, j=MAXN/2; i<MAXN-1; i++) {
        if (i < j) {
            swap(v[i], v[j]);
        }
        int x = MAXN / 2;
        while (x <= j) {
            j -= x;
            x >>= 1;
        }
        if (j < x) {
            j += x;
        }
    }

    for (int h=2; h<=MAXN; h<<=1) {
        for (int i=0; i<MAXN; i+=h) {
            for (int l=i; l<i+h/2; l++) {
                int r = l + h/2, idx = l-i;
                cd x = v[l], y = omg[inverse ? MAXN-(MAXN/h*idx) : MAXN/h*idx] * v[r];
                v[l] = x + y;
                v[r] = x - y;
            }
        }
    }

    if (inverse) {
        REP (i, MAXN) {
            v[i] /= MAXN;
        }
    }
}

void solve (char C) {
    int lst = -10000007;
    REP (i, MAXN) {
        a[i] = b[i] = 0;
    }
    REP (i, n) {
        if (s[i] == C) {
            lst = i;
        }
        if (i - lst <= k) {
            a[i] = 1;
        }
    }
    lst = 10000007;
    for (int i=n-1; i>=0; i--) {
        if (s[i] == C) {
            lst = i;
        }
        if (lst - i <= k) {
            a[i] = 1;
        }
    }


    REP (i, m) {
        if (t[i] == C) {
            b[m-1-i] = 1;
        }
    }

    FFT(a, 0);
    FFT(b, 0);
    REP (i, MAXN) {
        c[i] = a[i] * b[i];
    }
    FFT(c, 1);

    REP (i, n) {
        sum[i] += round(c[i].real());
    }
}

const double pi = acos(-1);
void build_omg () {
    omg[0] = omg[MAXN] = 1;
    REP1 (i, MAXN - 1) {
        omg[i] = polar(1.0, i*2*pi/MAXN);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    build_omg();

    cin >> n >> m >> k;
    cin >> s >> t;

    for (char c : {'A', 'T', 'G', 'C'}) {
        solve(c);
    }

    int ans = 0;
    REP (i, n) {
        ans += sum[i] == m;
    }

    cout << ans << endl;
    return 0;
}
