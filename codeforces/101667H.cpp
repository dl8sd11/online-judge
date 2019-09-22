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

vector<cd> a, b, c;
vector<int> ans;

void FFT (vector<cd> &v, int N, int d) {
    if (SZ(v) == 1) {
        return;
    }
    vector<cd> o(N>>1), e(N>>1);
    REP (i, (N>>1)) {
        e[i] = v[i<<1];
        o[i] = v[i<<1|1];
    }
    FFT(o, N>>1, d);
    FFT(e, N>>1, d);

    if (d > 0) {
        REP (i, (N>>1)) {
            v[i] = e[i] + omg[i*(MAXN/N)] * o[i];
            v[i+(N>>1)] = e[i] - omg[i*(MAXN/N)] * o[i];
        }
    } else {
        REP (i, (N>>1)) {
            v[i] = e[i] + omg[MAXN-i*(MAXN/N)] * o[i];
            v[i+(N>>1)] = e[i] - omg[MAXN-i*(MAXN/N)] * o[i];
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

    FFT(a, MAXN, 1);
    FFT(b, MAXN, 1);
    REP (i, MAXN) {
        c[i] = a[i] * b[i];
    }
    FFT(c, MAXN, -1);

    REP (i, n) {
        ans[i] += round(c[i].real() / MAXN);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    omg[0] = omg[MAXN] = 1;
    REP1 (i, MAXN-1) {
        omg[i] = polar(1.0, i*2*pi/MAXN);
    }
    a.resize(MAXN);
    b.resize(MAXN);
    c.resize(MAXN);

    cin >> s >> t;
    ans.resize(n);

    solve('R', 'S');
    solve('S', 'P');
    solve('P', 'R');

    int bst = 0;
    for (auto v : ans) {
        bst = max(bst, v);
    }

    cout << bst << endl;

    return 0;
}
