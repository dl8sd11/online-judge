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

const int MAXN = 1<<18;
const ll MOD = 1000000007;

typedef complex<double> cd;
const double pi = acos(-1);
cd omg[MAXN+1];

int n, m;
string s, t;

cd a[MAXN], b[MAXN], c[MAXN];
int ans[MAXN];

void FFT (cd *v, int d) {
    {
        for (int i=1,j=MAXN>>1;i<MAXN-1;i++) {
            if (i < j) {
                swap(v[i], v[j]);
            }
            int k = MAXN>>1;
            while (j >= k) {
                j -= k;
                k >>= 1;
            }
            if (j < k) {
                j += k;
            }
        }
    }

    for (int h=2; h<=MAXN; h<<=1) {
        for (int i=0; i<MAXN; i+=h) {
            for (int k=i; k<i+h/2; k++) {
                int l = k + h/2;
                int idx = k-i;
                cd x = v[k] - omg[d > 0 ? idx*(MAXN/h) : MAXN-idx*(MAXN/h)] * v[l];
                v[k] = v[k] + omg[d > 0 ? idx*(MAXN/h) : MAXN-idx*(MAXN/h)] * v[l];
                v[l] = x;
            }
        }
    }

    if (d < 0) {
        REP (i, MAXN) {
            v[i] /= MAXN;
        }
    }
}

void solve (char w, char l) {
    REP (i, MAXN) {
        a[i] = b[i] = 0;
    }
    REP (i, n) {
        a[i] = s[n-1-i] == l;
    }
    REP (i, m) {
        b[i] = t[i] == w;
    }

    FFT(a, 1);
    FFT(b, 1);
    REP (i, MAXN) {
        c[i] = a[i] * b[i];
    }
    FFT(c, -1);

    REP (i, n) {
        ans[i] += round(c[i].real());
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    omg[0] = omg[MAXN] = 1;
    REP1 (i, MAXN-1) {
        omg[i] = polar(1.0, i*2*pi/MAXN);
    }

    cin >> n >> m;
    cin >> s >> t;

    solve('R', 'S');
    solve('S', 'P');
    solve('P', 'R');

    int bst = 0;
    REP (i, n) {
        bst = max(bst, ans[i]);
    }

    cout << bst << endl;

    return 0;
}
