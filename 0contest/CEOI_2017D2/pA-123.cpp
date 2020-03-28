#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define eb emplace_back
#define X first
#define Y second
#define ALL(i) i.begin(),i.end()
#define MEM(i,a) memset(i,(a),sizeof(a))
#ifdef tmd
#define debug(...) fprintf(stderr,"%d(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x) {
    cerr<<x<<endl;
}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {
    cerr<<x<<",";
    _do(y...);
}
template<typename IT> ostream& _print(IT bg, IT ed, ostream &os) {
    for (IT it=bg;it!=ed; it++) {
        if (it==bg) {
            os << "{" << *it;
        } else {
            os << "," << *it;
        }
    }
    return os << "}";
}
template<typename IT> void pary (IT bg, IT ed) {
    _print(bg, ed, cerr);
}
template<typename T> ostream& operator<< (ostream &os, const vector<T> &vec) {
    return _print(vec.begin(), vec.end(),os);
}
#define IOS()
#else
#define endl '\n'
#define pary(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#endif // tmd

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 100005;
const int MAXC = 1000006;

int n, h[MAXN], w[MAXN];
ll s[MAXN], dp[MAXN];

struct Line {
    ll a, b;
    Line () {
        a = 0, b = INF;
    }
    Line (ll _a, ll _b) {
        a = _a, b = _b;
    }
    ll eval (ll x) {
        return a*x + b;
    }
};
Line seg[MAXC*4];

void addLine (Line cur, int o, int nL, int nR) {
    int nM = (nL + nR) >> 1;
    bool lg = seg[o].eval(nL) < cur.eval(nL);
    bool mg = seg[o].eval(nM) < cur.eval(nM);

    if (!mg) {
        swap(cur, seg[o]);
    }
    if (nL != nR - 1) {
        if (lg == mg) {
            addLine(cur, o<<1|1, nM, nR);
        } else {
            addLine(cur, o<<1, nL, nM);
        }
    }
}

ll f (ll x, int o, int nL, int nR) {
    if (nL == nR - 1) {
        return seg[o].eval(x);
    } else {
        int nM = (nL + nR) >> 1;
        if (x >= nM) {
            return min(seg[o].eval(x), f(x, o<<1|1, nM, nR));
        } else {
            return min(seg[o].eval(x), f(x, o<<1, nL, nM));
        }
    }
}
/*******GOODLUCK*********/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> h[i];
    }
    REP1 (i, n) {
        cin >> w[i];
        s[i] = s[i-1] + w[i];;
    }

    dp[1] = 0;
    addLine(Line{-2LL*h[1], 1LL*h[1]*h[1]-s[1]}, 1, 0, MAXC);
    debug(2LL*h[1], 1LL*h[1]*h[1]-s[1]);
    for (int i=2; i<=n; i++) {

        ll c = 1LL * h[i] * h[i] + s[i-1];
        ll mn = f(h[i], 1, 0, MAXC);
        debug(h[i], mn, c);
        dp[i] = mn + c;
        addLine(Line(-2LL*h[i], dp[i]+1LL*h[i]*h[i]-s[i]), 1, 0, MAXC);

    }
    pary(dp+1, dp+1+n);

    cout << dp[n] << endl;
    return 0;
}
