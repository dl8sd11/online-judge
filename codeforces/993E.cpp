#include <bits/stdc++.h>
using namespace std;
typedef double ld;
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

const ll MOD = 1000000007;
const int MAXN = 200005;

int pre[MAXN], cnt[MAXN], len;
bool ls[MAXN];
vector<complex<ld> > a, b, res;
complex<ld> ur[2][MAXN*4];
const ld pi = acos(-1);
void FFT(vector<complex<ld>> &v,int N,int t) {
    if (N == 1) {
        return;
    }
    vector<complex<ld> > o(N>>1),e(N>>1);
    REP (i,N>>1) {
        o[i] = v[i<<1];
        e[i] = v[i<<1|1];
    }
    FFT(o,N>>1,t),FFT(e,N>>1,t);

    //complex<ld> w1(cos(2*pi/N),t*sin(2*pi/N)),w0(1,0);
    complex<ld> w;
    for (ll i=0;i<(N>>1);i++) {
        w = ur[t == 1 ? 0 : 1][i * (len / N)];
        v[i] = o[i] + w*e[i];
        v[i+(N>>1)] = o[i] - w*e[i];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n, x;
    cin >> n >> x;

    int sum = 0;
    REP (i, n) {
        int d;
        cin >> d;
        ls[i] = d < x;
        sum += ls[i];
        pre[i] = sum;
        cnt[pre[i]]++;
    }
    cnt[0]++;

    len = 1;
    while (len < (n + 1) * 2) {
        len <<= 1;
    }

    ur[0][0] = ur[1][0] = 1;
    REP1 (i, len - 1) {
        ur[0][i] = polar(1.0, i*pi*2/len);
        ur[1][i] = polar(1.0, -i*pi*2/len);
    }

    debug(len);
    a.resize(len);
    b.resize(len);
    res.resize(len);

    REP (i, n+1) {
        a[i] = cnt[i];
        b[i] = cnt[n-i];
        debug(a[i], b[i]);
    }

    debug("FFT");
    FFT(a, len, 1);
    FFT(b, len, 1);
    REP (i, len) {
        res[i] = a[i] * b[i];
    }
    FFT(res, len, -1);

    vector<ll> ans(n+1);
    REP (i, n) {
        ans[n-i] = round(res[i].real() / len);
    }

    REP (i, MAXN) {
        ans[0] += ll(cnt[i]) * (cnt[i] - 1) / 2;
    }
    REP (i, n+1) {
        cout << ans[i] << " \n"[i==n];
    }
    return 0;
}
