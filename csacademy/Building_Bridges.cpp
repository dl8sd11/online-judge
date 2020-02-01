#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const int MAXC = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f;

int n, h[MAXN], w[MAXN];
ll dp[MAXN], wp[MAXN];
/*
Solution:
dp
dp[i] := minimum cost connecting piller i

dp[i] = min(dp[j]+(h[i]-h[j])^2+wp[i-1]-wp[j])
 = dp[j]+h[i]^2+h[j]^2-2*h[i]h[j]+wp[i-1]-wp[j]
 = (dp[j]-wp[j]+h[j]^2)+2*h[j]*h[i]+h[i]^2+wp[i-1]
*/

struct Line { // ax + b
    ll a, b;
    ll eval (const int x) const {
        return a * x + b;
    }

    Line () {
        a = 0;
        b = INF;
    }

    Line (ll x, ll y) : a(x), b(y){}
} seg[MAXC*4];

void add_line (Line nw, int o, int nL, int nR) {
    int nM = (nL + nR) >> 1;
    bool wL = seg[o].eval(nL) > nw.eval(nL);
    bool wM = seg[o].eval(nM) > nw.eval(nM);

    if (wM) {
        swap(nw, seg[o]);
    }
    if (nL != nR - 1) {
        if (wL != wM) {
            add_line(nw, o<<1, nL, nM);
        } else {
            add_line(nw, o<<1|1, nM, nR);
        }
    }
}

ll solve (int x, int o, int nL, int nR) {
    ll ret = seg[o].eval(x);
    int nM = (nL + nR) >> 1;
    if (nL != nR - 1) {
        if (x >= nM) {
            return min(ret, solve(x, o<<1|1, nM, nR));
        } else {
            return min(ret, solve(x, o<<1, nL, nM));
        }
    } else {
        return ret;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> h[i];
    }
    REP1 (i, n) {
        cin >> w[i];
        wp[i] = wp[i-1] + w[i];
    }

    dp[1] = 0;
    add_line(Line(-h[1]*2LL, 1LL*h[1]*h[1]-wp[1]), 1, 0, MAXC);

    for (int i=2;i<=n;i++) {
        dp[i] = solve(h[i], 1, 0, MAXC) + 1LL*h[i]*h[i]+wp[i-1];
        add_line(Line(-h[i]*2LL, 1LL*h[i]*h[i]-wp[i]+dp[i]), 1, 0, MAXC);
    }

    cout << dp[n] << endl;
}
